#include "cachefilter_factory.h"
#include <memory>
#include "cache/cacheresponse.h"
#include "cachefilter.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

	absl::StatusOr<Http::FilterFactoryCb> CacheFilterFactory::createFilterFactoryFromProto(const Protobuf::Message&, const std::string&, Server::Configuration::FactoryContext&)
{
	static CacheResponse cache(128);

	return [](Http::FilterChainFactoryCallbacks& callbacks) {
		auto filter = std::make_shared<CacheFilter>(cache);
		callbacks.addStreamFilter(filter);
	};
}

static Registry::RegisterFactory<CacheFilterFactory, Server::Configuration::NamedHttpFilterConfigFactory> registered_;

}
}
}
}
