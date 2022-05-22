-- Copied straight from imgui branch "features/premake"
project "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    staticruntime "off"

    targetdir "bin/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"
    objdir "bin-intr/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"

    files {
        "./*.cpp", "./*.h"
    }

    vpaths { ["imgui"] = { "../*.cpp", "../*.h", "../misc/debuggers/*.natvis" } }

    filter { "toolset:msc*" }
        files { "../misc/debuggers/*.natvis" }

    -- System Windows (WIN32)
    filter "system:windows"
		systemversion "latest"

    -- System Linux
	filter "system:linux"
		pic "On"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
