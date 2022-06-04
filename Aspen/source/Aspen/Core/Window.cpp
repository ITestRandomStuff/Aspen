#include "aspch.h"
#include "Window.h"

#include "Aspen/Debug/Log.h"
#include "Aspen/Event/WindowEvents.h"

#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace Aspen
{
	uint8_t Window::s_WindowCount = 0;

	void GLFWErrorCallback(int err, const char* desc)
	{
		ASP_ERROR("GLFW Error {0}, {1}", err, desc);
	}

	Window::Window(uint32_t width, uint32_t height, const std::string& title)
	{
		m_WindowData.size.x = width;
		m_WindowData.size.y = height;

		m_WindowData.title = title;

		if (s_WindowCount == 0)
		{
			int glfwInitSuccess = glfwInit();
			ASP_CRITICAL_ASSERT(!glfwInitSuccess, "Failed to initialize GLFW.");

			glfwSetErrorCallback(GLFWErrorCallback);
		}

		m_NativeWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		ASP_CRITICAL_ASSERT(!m_NativeWindow, "Failed to create window.");

		glfwSetWindowUserPointer(m_NativeWindow, &m_WindowData);
		glfwMakeContextCurrent(m_NativeWindow);

		glfwGetWindowPos(m_NativeWindow, &m_WindowData.position.x, &m_WindowData.position.y);

		{
			int gladInitSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			ASP_CRITICAL_ASSERT(!gladInitSuccess, "Failed to initialize GLAD.");
		}

		glfwSetWindowSizeCallback(m_NativeWindow, [](GLFWwindow* glfwWindow, int width, int height)
			{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(glfwWindow);
				data.size.x = width;
				data.size.y = height;

				WindowResizeEvent resizeEvent(width, height);
				data.eventCallback(resizeEvent);
			}
		);

		glfwSetWindowPosCallback(m_NativeWindow, [](GLFWwindow* glfwWindow, int posx, int posy)
			{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(glfwWindow);
				data.position.x = posx;
				data.position.y = posy;
			}
		);

		glfwSetWindowCloseCallback(m_NativeWindow, [](GLFWwindow* glfwWindow)
			{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(glfwWindow);

				WindowCloseEvent closeEvent = WindowCloseEvent();
				data.eventCallback(closeEvent);
			});

		++s_WindowCount;
	}

	Window::~Window()
	{
		Close();

		if (s_WindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_NativeWindow);
	}

	void Window::SetEventCallback(const std::function<void(Event&)>& clbk)
	{
		m_WindowData.eventCallback = clbk;
	}

	void Window::Close()
	{
		--s_WindowCount;
		glfwDestroyWindow(m_NativeWindow);
	}
}