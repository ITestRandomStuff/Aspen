#include "aspch.h"
#include "Window.h"

// STB_IMAGE_IMPLEMENTATION has to be in a .c or a .cpp file.
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>

#include "Aspen/Debug/Log.h"

#define CAST_VOIDPTR(ptr) (void*)ptr

namespace Aspen
{
	Window::Window(uint32_t width, uint32_t height, const std::string& title)
		:m_width(width), m_height(height), m_title(title)
	{
		glfwSetErrorCallback([](int err, const char* desc)
			{
				ASP_ERROR("GLFW Error " + std::to_string(err) + ", " + desc);
			}
		);

		m_nativeWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
		if (!m_nativeWindow)
		{
			glfwTerminate();
			ASP_CRIT("Failed to create a window.");

			return;
		}

		glfwSetWindowUserPointer(m_nativeWindow, this);
		glfwMakeContextCurrent(m_nativeWindow);

		glfwSetWindowSizeCallback(m_nativeWindow,
			[](GLFWwindow* natwindow, int width, int height)
			{
				Window* window = (Window*)glfwGetWindowUserPointer(natwindow);
				window->OnWindowResize(width, height);
			}
		);

		glfwSetWindowPosCallback(m_nativeWindow,
			[](GLFWwindow* natwindow, int posx, int posy)
			{
				Window* window = (Window*)glfwGetWindowUserPointer(natwindow);
				window->OnWindowPosition(posx, posy);
			}
		);

		glfwSetWindowCloseCallback(m_nativeWindow,
			[](GLFWwindow* natwindow)
			{
				Window* window = (Window*)glfwGetWindowUserPointer(natwindow);
				window->OnWindowClose();
			}
		);

		glfwSetWindowFocusCallback(m_nativeWindow,
			[](GLFWwindow* natwindow, int focused)
			{
				Window* window = (Window*)glfwGetWindowUserPointer(natwindow);
				window->OnWindowFocus(focused == GLFW_TRUE);
			}
		);

		glfwSetWindowIconifyCallback(m_nativeWindow,
			[](GLFWwindow* natwindow, int iconified)
			{
				Window* window = (Window*)glfwGetWindowUserPointer(natwindow);
				window->OnWindowIconify(iconified == GLFW_TRUE);
			}
		);

		glfwSetWindowMaximizeCallback(m_nativeWindow,
			[](GLFWwindow* natwindow, int maximized)
			{
				Window* window = (Window*)glfwGetWindowUserPointer(natwindow);
				window->OnWindowMaximize(maximized == GLFW_TRUE);
			}
		);
	}

	Window::~Window()
	{
		CloseWindow();
	}

	void Window::CloseWindow()
	{
		glfwDestroyWindow(m_nativeWindow);
		stbi_image_free(m_icon[0].pixels);
	}
	
	//==============================================//
	//==================| Events |==================//
	//==============================================//

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_nativeWindow);
	}

	void Window::OnWindowResize(uint32_t width, uint32_t height)
	{
		m_width = width;
		m_height = height;
		ASP_LOG("Window size (" + std::to_string(width) + ", " + std::to_string(height) + ")");
	}
	
	void Window::OnWindowPosition(int posx, int posy)
	{
		m_posx = posx;
		m_posy = posy;
		ASP_LOG("Window position (" + std::to_string(posx) + ", " + std::to_string(posy) + ")");
	}

	void Window::OnWindowClose()
	{
		m_destroyed = true;
		ASP_LOG("Window closed.");
	}

	void Window::OnWindowFocus(bool focused)
	{
		m_focused = focused;
		if (focused)
		{
			ASP_LOG("Window focused.");
		}
		else
		{
			ASP_LOG("Window not focused.");
		}
	}

	void Window::OnWindowIconify(bool iconified)
	{
		if (iconified)
		{
			ASP_LOG("Window has been iconified (minimized).");
		}
		else
		{
			ASP_LOG("Window has been restored.");
		}
	}

	void Window::OnWindowMaximize(bool maximized)
	{
		if (maximized)
		{
			ASP_LOG("Window has been maximized.");
		}
		else
		{
			ASP_LOG("Window has been restored.");
		}
	}

	//==============================================//
	//=================| Getter |===================//
	//==============================================//

	void Window::GetWindowSize(uint32_t& width, uint32_t height)
	{
		width = m_width;
		height = m_height;
	}

	void Window::GetWindowPosition(int& posx, int& posy)
	{
		posx = m_posx;
		posy = m_posy;
	}

	bool Window::IsFocused()
	{
		return m_focused;
	}

	bool Window::IsClosed()
	{
		return m_destroyed;
	}

	//==============================================//
	//=================| Setter |===================//
	//==============================================//

	void Window::SetIcon(const std::string& iconPath)
	{
		m_icon[0].pixels = stbi_load(iconPath.c_str(), &m_icon->width, &m_icon->height, 0, 4);
		if (m_icon[0].pixels)
		{
			glfwSetWindowIcon(m_nativeWindow, 1, m_icon);
		}
	}
}

#undef CAST_VOIDPTR