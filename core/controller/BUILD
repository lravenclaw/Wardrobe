load("@rules_qt//:qt.bzl", "qt_cc_library")

qt_cc_library(
	name = "client_controller",
	hdrs = ["client_controller.h"],
    srcs = ["client_controller.cpp"],
	deps = [
		"@rules_qt//:qt_core",
        "//core/model:client_model",
	],
	visibility = ["//visibility:public"],
)