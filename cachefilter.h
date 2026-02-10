#ifndef CACHEFILTER_H
#define CACHEFILTER_H

#include "envoy/http/filter.h"
#include "cache/cacheresponse.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

class CacheFilter {
	private:
		CacheResponse& cache_;

	public:
		CacheFilter(CacheResponse& cache);
};
}}}}

#endif
