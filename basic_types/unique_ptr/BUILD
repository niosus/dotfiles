load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "unique_ptr",
    hdrs = ["unique_ptr.hpp"],
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "example",
    srcs = ["example.cpp"],
    deps = [":unique_ptr"]
)
