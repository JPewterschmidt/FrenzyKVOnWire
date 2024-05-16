add_rules(
    "mode.tsan", "mode.ubsan", "mode.asan", 
    "mode.debug", "mode.release"
)

set_arch("x64")
includes("FrenzyKV")

set_languages("c++23", "c17")
set_policy("build.warning", true)
set_policy("build.optimization.lto", false)
add_requires("protobuf-cpp", "cxxopts")

add_packages("jeamalloc", "gtest")

target("FrenzyKVOnWireServer")
    set_kind("binary")
    add_deps("FrenzyKV", "koios", "toolpex")
    add_packages("protobuf-cpp", "cxxopts")
    add_includedirs(
        "./include",
        { public = false }
    )
    set_warnings("all", "error")
    add_cxflags("-Wconversion", { force = true })
    add_rules("protobuf.cpp")
    add_files(
        "server/*.cc", 
        "proto/*.proto", 
        { proto_public = true }
    )

target("FrenzyKVOnWireClient")
    set_kind("shared")
    add_deps("FrenzyKV", "koios", "toolpex")
    add_packages("protobuf-cpp")
    add_includedirs(
        "./include",
        { public = true }
    )
    set_warnings("all", "error")
    add_cxflags("-Wconversion", { force = true })
    add_rules("protobuf.cpp")
    add_files(
        "client/*.cc", 
        "proto/*.proto", 
        { proto_public = true }
    )

target("FrenzyKVOnWire-test")
    set_kind("binary")
    add_deps("FrenzyKV", "koios", "toolpex")
    add_cxflags("-Wconversion", { force = true })
    set_warnings("all", "error")
    add_packages("protobuf-cpp")
    add_rules("protobuf.cpp")
    add_includedirs(
        "./include",
        { public = true }
    )
    add_files("test/*.cc")
    add_files(
        "proto/*.proto", 
        { proto_public = true }
    )
    after_build(function (target)
        os.exec(target:targetfile())
        print("xmake: unittest complete.")
    end)
    on_run(function (target)
        --nothing
    end)
