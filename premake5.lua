workspace "Aspen"
    configurations { "Debug", "Release" }
    architecture "x86_64"

project "Aspen"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"  -- Using C++20 for std::erase_if

    location "Aspen"

    targetdir "bin/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/Aspen"
    objdir "bin-intr/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/Aspen"

    pchsource "Aspen/source/aspch.cpp"
    pchheader "aspch.h"

    files {
        "Aspen/source/**.h", "Aspen/source/**.cpp"
    }

    includedirs {
        "Aspen/source",
        "Aspen/vendor",
        "Aspen/vendor/spdlog/include",
        "Aspen/vendor/GLFW/include"
    }

    links {
        "opengl32.lib",
        "Aspen/vendor/GLFW/lib-vc2022/glfw3_mt.lib"
    }

    filter "configurations:Debug"
        defines { "ASP_CONFIG_DEBUG" }
        symbols "on"

    filter "configurations:Release"
        defines { "ASP_CONFIG_RELEASE" }
        optimize "on"
