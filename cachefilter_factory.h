#pragma once

#include <memory>
#include <string>
#include "envoy/server/filter_config.h"
#include "envoy/registry/registry.h"
#include "envoy/http/filter.h"
#include "cachefilter.h"
#include "cache/cacheresponse.h"
#include "envoy/config/core/v3/base.pb.h"
#include "google/protobuf/empty.pb.h"
#include "cachefilter.pb.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace Cache_B {

class CacheFilterFactory : public Server::Configuration::NamedHttpFilterConfigFactory {
	public:
		absl::StatusOr<Http::FilterFactoryCb> createFilterFactoryFromProto(const Protobuf::Message& proto_config, const std::string&, Server::Configuration::FactoryContext& context) override;
		ProtobufTypes::MessagePtr createEmptyConfigProto() override {
			return std::make_unique<google::protobuf::Empty>();
		};

		std::string name() const override {
			return "cache_b";
		};
};

}
}
}
}
