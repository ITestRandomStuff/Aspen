workspace "Aspen"
    configurations { "Debug", "Release" }
    architecture "x86_64"

project "Aspen"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    location "Aspen"

    targetdir "bin/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/Aspen"
    objdir "bin-intr/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/Aspen"

    files {
        "Aspen/source/Aspen/**.h", "Aspen/source/Aspen/**.cpp"
    }

    includedirs {
        "Aspen/source"
    }

    links {
        "opengl32.lib"
    }

    filter "configurations:Debug"
        defines { "ASP_CONFIG_DEBUG" }
        symbols "on"

    filter "configurations:Release"
        defines { "ASP_CONFIG_RELEASE" }
        optimize "on"
