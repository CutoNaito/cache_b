load(
	"//bazel:envoy_build_system.bzl",
	"envoy_cc_extension",
	"envoy_extension_package",
)

licenses(["notice"])  # Apache 2

# Needed to generate config_envoy_extension target
envoy_extension_package()

proto_library(
    name = "cachefilter_proto",
    srcs = ["cachefilter.proto"],
)

cc_proto_library(
	name = "cachefilter_cc",
	deps = [":cachefilter_proto"],
)

# All filter code goes inside envoy_cc_extension
envoy_cc_extension(
	name = "config",
	srcs = glob([
		"cachefilter.cc",
		"cachefilter_factory.cc",
		"cache/**/*.cpp",
	]),
	hdrs = glob([
		"cachefilter.h",
		"cachefilter_factory.h",
		"cache/**/*.h",
	]),
	deps = [
    "//envoy/http:filter_interface",
    "//envoy/server:filter_config_interface",
    "//envoy/registry",
    "//source/extensions/filters/http/common:factory_base_lib",
    "//source/common/protobuf",
    ":cachefilter_cc",
	],
	visibility = ["//visibility:public"],
)
