load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_library",
    "envoy_extension_package",
)

licenses(["notice"])  # Apache 2

## WIP: Simple in-memory cache storage plugin. Not ready for deployment.

envoy_extension_package()

envoy_cc_library(
    name = "cache_b",
    srcs = [
		"cachefilter.cc",
		"cachefilter_factory.cc",
	],
    hdrs = [
		"cachefilter.h",
		"cachefilter_factory.h",
	],
    deps = [
		"//envoy/http:filter_interface",
		"//envoy/server:filter_config_interface",
		"//envoy/registry",
		"//source/common/protobuf",
		"//external:protobuf",
    ],
)
