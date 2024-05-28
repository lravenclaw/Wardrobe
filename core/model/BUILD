load("@rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
	name = "item_model",
	hdrs = ["item_info.h"],
    srcs = ["item_info.cpp"],
	deps = [
		"@rules_qt//:qt_core",
	],
	visibility = ["//visibility:public"],
)