-- THE CHERNO'S GLAD PREMAKE5 FILE

project "glad"
	kind "StaticLib"
	language "C"

	targetdir "bin/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"
    objdir "bin-intr/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"

	files {
		"include/**.h",
		"src/**.c", "src/**.h"
	}

	includedirs {
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"