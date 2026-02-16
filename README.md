# A custom Envoy request cache extension

## Description

This is a [CDN77 recruit task](https://docs.google.com/document/d/1ivIVC0zlOY5AMpe9Wyc2ox5hHkAsh2HPW8hX8-UzXzs/edit?tab=t.0) focused on patching Envoy with a simple C++ cache for HTTP requests.

## Usage & Installation

Clone [Envoy](https://github.com/envoyproxy/envoy) and cd inside

Clone this repository inside `source/extensions/filters/http/`

Build Envoy with `bazel build //source/exe:envoy-static`

Run Envoy with `bazel-bin/source/exe/envoy-static --config-path source/extensions/filters/http/cache_b/config.yaml` (or use your own YAML config file)

## Resources

https://www.envoyproxy.io/docs/envoy/v1.37.0/intro/arch_overview/http/http_filters.html

https://www.envoyproxy.io/docs/envoy/v1.37.0/api/api

https://deepwiki.com/envoyproxy/envoy-filter-example/5-http-filter-example

https://github.com/envoyproxy/envoy-filter-example/tree/main/http-filter-example

https://info.varnish-software.com/blog/request-coalescing-and-other-reasons-to-use-varnish-as-an-origin-shield

Other already existing Envoy extensions

https://http.dev/caching
