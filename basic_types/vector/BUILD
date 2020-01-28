load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "vector",
    hdrs = ["vector.hpp"],
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "example",
    srcs = ["example.cpp"],
    deps = [":vector"]
)
