load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "shared_ptr",
    hdrs = ["shared_ptr.hpp"],
    visibility = ["//visibility:public"]
)

cc_binary(
    name = "example",
    srcs = ["example.cpp"],
    deps = [":shared_ptr"]
)
