#pragma once

#include <memory>
#include <string>
#include "envoy/server/filter_config.h"
#include "envoy/registry/registry.h"
#include "envoy/http/filter.h"
#include "cachefilter.h"
#include "cache/cacheresponse.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

class CacheFilterFactory : public Server::Configuration::NamedHttpFilterConfigFactory {
	public:
		Http::FilterFactoryCb createFilterFactoryFromPhoto(const Protobuf::Message& proto_config, const std::string&, FactoryContext& context) override;
		ProtobufTypes::MessagePtr createEmptyConfigPhoto() override {
			return std::make_unique<ProtobufWkt::Empty>();
		};

		std::string name() const override {
			return "cache_b";
		};
};

}
}
}
}
