load("@rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
	name = "item_controller",
	hdrs = ["item_controller.h"],
    srcs = ["item_controller.cpp"],
	deps = [
		"@rules_qt//:qt_core",
		"@magic_enum//:magic_enum",
        "//core/model:item_model",
	],
	visibility = ["//visibility:public"],
)