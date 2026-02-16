#include <algorithm>
#include <string>

#include "absl/types/optional.h"
#include "cache/httpresponse.h"
#include "cachefilter.h"
#include "cachemanager.h"
#include "envoy/http/header_map.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

CacheFilter::CacheFilter(CacheManager& manager) : manager_(manager) {}

Http::FilterHeadersStatus CacheFilter::decodeHeaders(Http::RequestHeaderMap& headers, bool)
{
	auto host = headers.getHostValue();
	auto path = headers.getPathValue();

	current_key_ = std::string(host) + "|" + std::string(path);
	HttpResponse* cached = nullptr;

	if (manager_.cache()->lookup(current_key_, &cached)) {
		decoder_callbacks_->sendLocalReply(
			static_cast<Http::Code>(cached->get_code()),
			cached->get_body(),
			[](Http::ResponseHeaderMap& headers) {
				headers.addCopy(Http::LowerCaseString("x-cache-status"), "HIT");
			},
			absl::nullopt,
			"cache_hit"
		);

		return Http::FilterHeadersStatus::StopIteration;
	}

	if (auto* existing = manager_.findInFlight(current_key_)) {
		in_flight_ = existing;
		existing->filters.push_back(this);
		ENVOY_LOG(info, "coalesced for {}", current_key_);

		return Http::FilterHeadersStatus::StopIteration;
	}

	in_flight_ = manager_.createInFlight(current_key_);
	in_flight_->filters.push_back(this);
	should_cache_ = true;

	ENVOY_LOG(info, "going upstream for {}", current_key_);
	return Http::FilterHeadersStatus::Continue;
}

Http::FilterHeadersStatus CacheFilter::encodeHeaders(Http::ResponseHeaderMap& headers, bool)
{
	if (!in_flight_) {
		return Http::FilterHeadersStatus::Continue;
	}

	auto status = headers.getStatusValue();

	if (status != "200") {
		should_cache_ = false;
	}

	in_flight_->response_code = std::stoi(std::string(status));
	headers.iterate([this](const Http::HeaderEntry& entry) {
		in_flight_->headers.emplace_back(
			std::string(entry.key().getStringView()),
			std::string(entry.value().getStringView())
		);

		return Http::HeaderMap::Iterate::Continue;
	});

	headers.addCopy(Http::LowerCaseString("x-cache-status"), "MISS");

	return Http::FilterHeadersStatus::Continue;
}

void CacheFilter::setDecoderFilterCallbacks(Http::StreamDecoderFilterCallbacks& callbacks)
{
	decoder_callbacks_ = &callbacks;
}

void CacheFilter::setEncoderFilterCallbacks(Http::StreamEncoderFilterCallbacks& callbacks)
{
	encoder_callbacks_ = &callbacks;
}

Http::FilterDataStatus CacheFilter::decodeData(Buffer::Instance&, bool)
{
	return Http::FilterDataStatus::Continue;
}

Http::FilterDataStatus CacheFilter::encodeData(Buffer::Instance& data, bool end_stream)
{
	if (!in_flight_) {
		return Http::FilterDataStatus::Continue;
	}

	in_flight_->buffered_body.add(data);

	if (!end_stream) {
		return Http::FilterDataStatus::Continue;
	}

	in_flight_->upstream_finished = true;

	if (should_cache_) {
		HttpResponse response(
			current_key_,
			"",
			"",
			in_flight_->buffered_body.toString(),
			in_flight_->response_code
		);

		manager_.cache()->insert(std::move(response));
	}


	for (auto* filter : in_flight_->filters) {
		if (filter != this) {
			auto& dispatcher = filter->decoder_callbacks_->dispatcher();
			dispatcher.post([filter]() {
				filter->decoder_callbacks_->continueDecoding();
			});
		}
	}

	manager_.deleteInFlight(current_key_);

	return Http::FilterDataStatus::Continue;
}

Http::FilterTrailersStatus CacheFilter::decodeTrailers(Http::RequestTrailerMap&)
{
	return Http::FilterTrailersStatus::Continue;
}

Http::FilterTrailersStatus CacheFilter::encodeTrailers(Http::ResponseTrailerMap&)
{
	return Http::FilterTrailersStatus::Continue;
}

void CacheFilter::onDestroy()
{
	if (!in_flight_) {
		return;
	}

	auto& filters = in_flight_->filters;
	filters.erase(std::remove(filters.begin(), filters.end(), this), filters.end());
}

}
}
}
}
