#include "cachefilter_factory.h"
#include <memory>
#include "cache/cacheresponse.h"
#include "cachefilter.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

Http::FilterFactoryCb CacheFilterFactory::createFilterFactoryFromPhoto(Protobuf::Message&, std::string&, Server::Configuration::FactoryContext&)
{
	static CacheResponse cache(128);

	return [&cache](Http::FilterChainFactoryCallbacks& callbacks) -> void {
		auto filter = std::make_shared<CacheFilter>(cache);
		callbacks.addStreamFilter(filter);
	}
}

REGISTER_FACTORY(CacheFilterFactory, Server::Configuration::NamedHttpFilterConfigFactory);

}
}
}
}
