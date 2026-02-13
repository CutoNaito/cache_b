#ifndef CACHEFILTER_H
#define CACHEFILTER_H

#include "envoy/http/filter.h"
#include "envoy/http/header_map.h"
#include "envoy/buffer/buffer.h"
#include "absl/types/optional.h"
#include "cache/cacheresponse.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

class CacheFilter : public Http::StreamDecoderFilter, public Http::StreamEncoderFilter {
	private:
		CacheResponse& cache_;

		Http::StreamDecoderFilterCallbacks* decoder_callbacks_{};
		Http::StreamEncoderFilterCallbacks* encoder_callbacks_{};
		std::string current_key_;

	public:
		CacheFilter(CacheResponse& cache);

		Http::FilterHeadersStatus decodeHeaders(Http::RequestHeaderMap& headers, bool end_stream) override;
		Http::FilterHeadersStatus encodeHeaders(Http::ResponseHeaderMap& headers, bool end_stream) override;

		Http::FilterTrailersStatus decodeTrailers(Http::RequestTrailerMap&) override;
		Http::FilterTrailersStatus encodeTrailers(Http::ResponseTrailerMap&) override;

		Http::FilterDataStatus decodeData(Buffer::Instance&, bool) override;
		Http::FilterDataStatus encodeData(Buffer::Instance& data, bool end_stream) override;

		void setDecoderFilterCallbacks(Http::StreamDecoderFilterCallbacks& callbacks) override;
		void setEncoderFilterCallbacks(Http::StreamEncoderFilterCallbacks& callbacks) override;

		void onDestroy() override {};
};
}
}
}
}

#endif
