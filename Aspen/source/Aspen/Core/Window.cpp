#include "aspch.h"
#include "Window.h"

#include <filesystem>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

namespace Aspen
{
	uint8_t Window::s_windows = 0;

	Window::Window(
		uint32_t width,
		uint32_t height,
		const std::string& title,
		const std::string& iconPath)
	:m_width(width), m_height(height), m_title(title)
	{
		// Initialize glfw.
		if (s_windows == 0)
		{
			int glfwSuccess = glfwInit();
			ASP_CRIT_ASSERT(!glfwSuccess, "Failed to initialize GLFW.");
		}

		// Create window.
		m_window = glfwCreateWindow(m_width, m_height, title.c_str(), nullptr, nullptr);
		if (!m_window)
		{
			ASP_CRIT("Failed to create a GLFW window.");
			glfwTerminate();
		}

		// Create icon and set it.
		m_icon[0].pixels = stbi_load(iconPath.c_str(), &m_icon[0].width, &m_icon[0].height, 0, 4);
		if (m_icon[0].pixels) glfwSetWindowIcon(m_window, 1, m_icon);
		else ASP_ERROR("Failed to set window icon.");

		/*
		tests if the icon path is valid, needs fstream
		std::ifstream infile(iconPath.c_str());
		if (infile.good()) ASP_LOG("Icon Path is valid.");
		else ASP_LOG("Icon Path is invalid.");*/

		// Set window positions.
		glfwGetWindowPos(m_window, &m_posX, &m_posY);

		// Set the user pointer.
		glfwSetWindowUserPointer(m_window, this);

		// Make context to current one.
		glfwMakeContextCurrent(m_window);

		// Set callbacks.
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* nativeWindow, int width, int height)
			{
				Window* window = (Window*)glfwGetWindowUserPointer(nativeWindow);
				window->OnWindowResize(width, height);
			});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* nativeWindow)
			{
				Window* window = (Window*)glfwGetWindowUserPointer(nativeWindow);
				window->OnWindowClose();
			});

		glfwSetWindowPosCallback(m_window, [](GLFWwindow* nativeWindow, int posX, int posY)
			{
				Window* window = (Window*)glfwGetWindowUserPointer(nativeWindow);
				window->OnWindowReposition(posX, posY);
			});

		glfwSetWindowFocusCallback(m_window, [](GLFWwindow* nativeWindow, int focused)
			{
				Window* window = (Window*)glfwGetWindowUserPointer(nativeWindow);
				window->OnWindowFocus(focused == GLFW_TRUE);
			});

		// Increment s_windows.
		s_windows += 1;
	}

	Window::~Window()
	{

	}

	void Window::OnUpdate()
	{
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	//==================================================//
	//******************* Events ***********************//
	//==================================================//

	void Window::OnWindowResize(uint32_t width, uint32_t height)
	{
		m_width = width;    m_height = height;
		ASP_LOG("{0}, {1}", width, height);
	}

	void Window::OnWindowReposition(int posX, int posY)
	{
		m_posX = posX;    m_posY = posY;
		ASP_LOG("{0}, {1}", posX, posY);
	}

	void Window::OnWindowClose()
	{
		if (m_destroyed) return;
		ASP_LOG("A window has been closed.");

		glfwDestroyWindow(m_window);

		s_windows -= 1U;
		if (s_windows == 0)
			glfwTerminate();

		m_destroyed = true;
	}

	void Window::OnWindowFocus(bool focused)
	{
		m_focused = focused;
		ASP_LOG("{0}", focused);
	}

	//==================================================//
	//******************* Getters **********************//
	//==================================================//

	bool Window::GetWindowFocus() const
	{
		return m_focused;
	}

	bool Window::IsWindowClosed() const
	{
		return m_destroyed;
	}

	void Window::GetWindowSize(uint32_t& width, uint32_t& height) const
	{
		width = m_width;	height = m_height;
	}

	void Window::GetWindowPosition(int& x, int& y) const
	{
		x = m_posX;    y = m_posY;
	}
}