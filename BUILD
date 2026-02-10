load(
    "//bazel:envoy_build_system.bzl",
    "envoy_cc_extension",
    "envoy_extension_package",
)

licenses(["notice"])  # Apache 2

## WIP: Simple in-memory cache storage plugin. Not ready for deployment.

envoy_extension_package()

envoy_cc_extension(
    name = "config",
    srcs = ["cachefilter.cc"],
    hdrs = ["cachefilter.h"],
    deps = [
		"//include/envoy/http:filter_interface"
    ],
)
