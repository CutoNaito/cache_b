#include "cachefilter.h"
#include "cache/cacheresponse.h"
#include "cache/httpresponse.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

CacheFilter::CacheFilter(CacheResponse& cache) : cache_(cache) {}

Http::FilterHeadersStatus CacheFilter::decodeHeaders(Http::RequestHeaderMap& headers, bool)
{
	auto host = headers.getHostValue();
	auto path = headers.getPathValue();

	current_key_ = std::string(host) + "|" + std::string(path);
	HttpResponse* cached = nullptr;

	if (cache_.lookup(current_key_, &cached)) {
		decoder_callbacks_->sendLocalReply(
			static_cast<Http::Code>(cached->get_code()),
			cached->get_body(),
			nullptr,
			absl::nullopt,
			"cache_hit"
		);

		return Http::FilterHeadersStatus::StopIteration;
	}

	return Http::FilterHeadersStatus::Continue;
}

Http::FilterHeadersStatus CacheFilter::encodeHeaders(Http::ResponseHeaderMap& headers, bool)
{
	auto status = headers.getStatusValue();

	if (status != "200") {
		return Http::FilterHeadersStatus::Continue;
	}

	std::string body = "";

	HttpResponse response(
		"",
		"",
		body,
		200
	);

	cache_.insert(std::move(response));

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
	if (!should_cache_) {
		return Http::FilterDataStatus::Continue;
	}

	response_body_.append(data.toString());

	if (end_stream) {
		HttpResponse response(
			"",
			"",
			response_body_,
			response_code_
		);

		cache_.insert(std::move(response));
	}

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

}
}
}
}
