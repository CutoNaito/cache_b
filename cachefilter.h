#pragma once

#include "absl/types/optional.h"
#include "cache/cacheresponse.h"
#include "cachemanager.h"
#include "envoy/buffer/buffer.h"
#include "envoy/http/filter.h"
#include "envoy/http/header_map.h"
#include "source/common/common/logger.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

class CacheFilter : public Http::StreamFilter, public Logger::Loggable<Logger::Id::filter> {
	private:
		CacheManager& manager_;
		std::string current_key_;
		InFlightRequest* in_flight_{nullptr};
		bool should_cache_{false};

		Http::StreamDecoderFilterCallbacks* decoder_callbacks_{};
		Http::StreamEncoderFilterCallbacks* encoder_callbacks_{};

	public:
		CacheFilter(CacheManager& manager);

		Http::FilterHeadersStatus decodeHeaders(Http::RequestHeaderMap& headers, bool end_stream) override;
		Http::FilterHeadersStatus encodeHeaders(Http::ResponseHeaderMap& headers, bool end_stream) override;

		Http::FilterTrailersStatus decodeTrailers(Http::RequestTrailerMap&) override;
		Http::FilterTrailersStatus encodeTrailers(Http::ResponseTrailerMap&) override;

		Http::FilterDataStatus decodeData(Buffer::Instance&, bool) override;
		Http::FilterDataStatus encodeData(Buffer::Instance& data, bool end_stream) override;

		void setDecoderFilterCallbacks(Http::StreamDecoderFilterCallbacks& callbacks) override;
		void setEncoderFilterCallbacks(Http::StreamEncoderFilterCallbacks& callbacks) override;

		void onDestroy() override;

		Http::Filter1xxHeadersStatus encode1xxHeaders(Http::ResponseHeaderMap&) override {
			return Http::Filter1xxHeadersStatus::Continue;
		}

		Http::FilterMetadataStatus encodeMetadata(Http::MetadataMap&) override {
			return Http::FilterMetadataStatus::Continue;
		}
};

}
}
}
}
