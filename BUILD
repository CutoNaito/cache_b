load(
	"//bazel:envoy_build_system.bzl",
	"envoy_cc_extension",
	"envoy_extension_package",
)

envoy_extension_package()

proto_library(
	name = "cachefilter_proto",
	srcs = ["cachefilter.proto"],
)

cc_proto_library(
	name = "cachefilter_cc",
	deps = [":cachefilter_proto"],
)

envoy_cc_extension(
	name = "config",
	srcs = glob([
		"cachefilter.cc",
		"cachefilterconfig.cc",
		"cachemanager.cc",
		"cache/**/*.cc",
	]),
	hdrs = glob([
		"cachefilter.h",
		"cachefilterconfig.h",
		"cachemanager.h",
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
