#pragma once

#include <memory>
#include <string>

#include "cache/cacheresponse.h"
#include "cachefilter.h"
#include "envoy/config/core/v3/base.pb.h"
#include "envoy/http/filter.h"
#include "envoy/registry/registry.h"
#include "envoy/server/filter_config.h"
#include "google/protobuf/empty.pb.h"
#include "source/extensions/filters/http/cache_b/cachefilter.pb.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

class CacheFilterConfig : public Server::Configuration::NamedHttpFilterConfigFactory {
	public:
		absl::StatusOr<Http::FilterFactoryCb> createFilterFactoryFromProto(const Protobuf::Message& proto_config, const std::string&, Server::Configuration::FactoryContext& context) override;
		ProtobufTypes::MessagePtr createEmptyConfigProto() override {
			return std::make_unique<envoy::extensions::filters::http::cache_b::v3::CacheFilterConfig>();
		};

		std::string name() const override {
			return "cache_b";
		};
};

}
}
}
}
