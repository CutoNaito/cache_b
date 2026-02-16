#include <memory>

#include "cache/cacheresponse.h"
#include "cachefilter.h"
#include "cachefilterconfig.h"
#include "cachemanager.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

absl::StatusOr<Http::FilterFactoryCb> CacheFilterConfig::createFilterFactoryFromProto(const Protobuf::Message&, const std::string&, Server::Configuration::FactoryContext&) {
	static auto cache = std::make_shared<CacheResponse>(128);
	static CacheManager manager(cache);

	return [](Http::FilterChainFactoryCallbacks& callbacks) {
		auto filter = std::make_shared<CacheFilter>(manager);
		callbacks.addStreamFilter(filter);
	};
}

static Registry::RegisterFactory<CacheFilterConfig, Server::Configuration::NamedHttpFilterConfigFactory> registered_;

}
}
}
}
