load("@rules_qt//:qt.bzl", "qt_cc_binary", "qt_cc_library", "qt_ui_library")

qt_ui_library(
    name = "main_window_ui",
    ui = "main_window.ui",
    deps = [
        "@rules_qt//:qt_widgets",
    ],
)

qt_cc_library(
	name = "main_window",
	hdrs = ["main_window.h"],
	srcs = ["main_window.cpp"],
	deps = [
		"@rules_qt//:qt_core",
		"@rules_qt//:qt_widgets",
		"//core/model:item_model",
		"//core/controller:item_controller",
		"//resources:resources_qrc",
	],
)

qt_cc_binary(
	name = "app",
	srcs = ["main.cpp"],
	deps = [
		"@rules_qt//:qt_core",
		"@rules_qt//:qt_widgets",
		"//app:main_window",
		"//core/model:item_model",
		"//core/controller:item_controller",
	],
)

