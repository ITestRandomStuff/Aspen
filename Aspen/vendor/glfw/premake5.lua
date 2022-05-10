-- THE CHERNO'S GLFW PREMAKE FILE

project "glfw"
    kind "StaticLib"
    language "C"

    targetdir "bin/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"
    objdir "bin-intr/%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}/%{prj.name}"

    files {
        -- Everything in the include dir: glfw3.h and glfw3native.h.
        "include/GLFW/**.h",
        
        -- Everything in src dir, that isn't platform specific.
        "src/glfw_config.h",
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/monitor.c",
		"src/vulkan.c",
		"src/window.c"
    }

    -- System Windows (WIN32)
    filter "system:windows"
        systemversion "latest"
        staticruntime "on"

        defines {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        files
		{
			"src/win32_init.c",
			"src/win32_joystick.c",
			"src/win32_monitor.c",
			"src/win32_time.c",
			"src/win32_thread.c",
			"src/win32_window.c",

			"src/wgl_context.c",
			"src/egl_context.c",

			"src/osmesa_context.c"
		}

    -- System Linux
    filter "system:linux"
        systemversion "latest"
        staticruntime "on"

        defines {
            "_GLFW_X11"
        }

        files
		{
			"src/x11_init.c",
			"src/x11_monitor.c",
			"src/x11_window.c",
			"src/xkb_unicode.c",
			"src/posix_time.c",
			"src/posix_thread.c",

			"src/glx_context.c",
			"src/egl_context.c",

			"src/osmesa_context.c",
			"src/linux_joystick.c"
		}

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"