#include <memory>
#include <mutex>
#include <string>

#include "cachemanager.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

InFlightRequest* CacheManager::findInFlight(const std::string& key)
{
	std::lock_guard<std::mutex> lock(mutex_);

	auto it = in_flight_.find(key);

	if (it == in_flight_.end()) {
		return nullptr;
	}

	return it->second.get();
}

InFlightRequest* CacheManager::createInFlight(const std::string& key)
{
	std::lock_guard<std::mutex> lock(mutex_);

	auto req = std::make_unique<InFlightRequest>();
	auto* ptr = req.get();
	
	in_flight_[key] = std::move(req);

	return ptr;
}

void CacheManager::deleteInFlight(const std::string& key)
{
	std::lock_guard<std::mutex> lock(mutex_);

	in_flight_.erase(key);
}

}
}
}
}
