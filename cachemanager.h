#pragma once

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "cache/cacheresponse.h"
#include "envoy/buffer/buffer.h"
#include "envoy/http/header_map.h"
#include "source/common/buffer/buffer_impl.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

class CacheFilter;

struct InFlightRequest {
	bool upstream_finished{false};
	int response_code;
	std::vector<std::pair<std::string, std::string>> headers;
	Buffer::OwnedImpl buffered_body;
	std::vector<CacheFilter*> filters;
};

class CacheManager {
	public:
		CacheManager(std::shared_ptr<CacheResponse> cache) : cache_(std::move(cache)) {}
		std::shared_ptr<CacheResponse> cache() { return cache_; }
		InFlightRequest* findInFlight(const std::string& key);
		InFlightRequest* createInFlight(const std::string& key);
		void deleteInFlight(const std::string& key);

	private:
		std::mutex mutex_;
		std::shared_ptr<CacheResponse> cache_;
		std::unordered_map<std::string, std::unique_ptr<InFlightRequest>> in_flight_;
};

}
}
}
}
