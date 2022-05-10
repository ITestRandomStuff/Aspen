workspace "Aspen"
    configurations { "Debug", "Release" }
    architecture "x86_64"

IncludeDirs = {}
IncludeDirs["glfw"] = "Aspen/vendor/glfw/include"
IncludeDirs["glad"] = "Aspen/vendor/glad/include"

IncludeDirs["spdlog"] = "Aspen/vendor/spdlog/include"
IncludeDirs["stb_image"] = "Aspen/vendor/stb_image/include"

include "Aspen/vendor/glfw"
include "Aspen/vendor/glad"

project "Aspen"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    location "%{prj.name}"

    targetdir "bin/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"
    objdir "bin-intr/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"

    pchsource "Aspen/source/aspch.cpp"
    pchheader "aspch.h"

    files {
        "Aspen/source/**.h", "Aspen/source/**.cpp"
    }

    includedirs {
        "Aspen/source",
        "%{IncludeDirs.glfw}",
        "%{IncludeDirs.glad}",

        "%{IncludeDirs.spdlog}",
        "%{IncludeDirs.stb_image}"
    }

    links {
        "opengl32.lib",
        "glfw",
        "glad"
    }

    filter "configurations:Debug"
        defines { "ASP_CONFIG_DEBUG" }
        symbols "on"

    filter "configurations:Release"
        defines { "ASP_CONFIG_RELEASE" }
        optimize "on"
