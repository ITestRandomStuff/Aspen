#include "aspch.h"
#include "Window.h"

#include "Aspen/Events/AppEvents.h"
#include "Aspen/Events/KeyEvents.h"

#include "glad/glad.h"

namespace Aspen
{
	uint8_t Window::s_WindowCount = 0;

	Window::Window(uint32_t width, uint32_t height, const std::string& title, bool fullscreen)
	{
		// Set window data.
		m_WindowData.size.x = width;
		m_WindowData.size.y = height;
		m_WindowData.title = title;

		// Initialize GLFW if no windows have been created.
		if (s_WindowCount == 0)
		{
			int glfwInitSuccess = glfwInit();
			ASP_CRIT_ASSERT(!glfwInitSuccess, "Failed to initialize GLFW.");

			// Set the error callback.
			glfwSetErrorCallback([](int err, const char* desc)
				{
					ASP_ERROR("GLFW Error {0}, {1}", err, desc);
				}
			);
		}

		// Create window with GLFW.
		ASP_ASSERT(fullscreen, "Fullscreen not supported!");
		m_nativeWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		ASP_CRIT_ASSERT(m_nativeWindow == NULL, "Failed to create window.");

		// Set window data position.
		glfwGetWindowPos(m_nativeWindow, &m_WindowData.position.x, &m_WindowData.position.y);

		// Make context current.
		glfwMakeContextCurrent(m_nativeWindow);
		SetVSync(true);

		// Set window user pointer.
		glfwSetWindowUserPointer(m_nativeWindow, &m_WindowData);

		// Initialize GLAD.
		int gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ASP_CRIT_ASSERT(!gladSuccess, "Failed to initialize GLAD.");

		ASP_LOG("OpenGL Vendor: {0}", (char*)glGetString(GL_VENDOR));
		ASP_LOG("OpenGL Renderer: {0}", (char*)glGetString(GL_RENDERER));
		ASP_LOG("OpenGL Version: {0}", (char*)glGetString(GL_VERSION));

		// Set event callbacks.
		glfwSetWindowSizeCallback(m_nativeWindow, [](GLFWwindow* glfwWindow, int width, int height)
			{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(glfwWindow);
				data.size.x = width;
				data.size.y = height;

				WindowResizeEvent resizeEvent(width, height);
				data.eventCallback(resizeEvent);
			}
		);

		glfwSetWindowPosCallback(m_nativeWindow, [](GLFWwindow* glfwWindow, int x, int y)
			{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(glfwWindow);
				data.position.x = x;
				data.position.y = y;

				WindowPositionEvent positionEvent(x, y);
				data.eventCallback(positionEvent);
			}
		);

		glfwSetWindowCloseCallback(m_nativeWindow, [](GLFWwindow* glfwWindow)
			{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(glfwWindow);

				WindowCloseEvent closeEvent;
				data.eventCallback(closeEvent);
			}
		);
		
		glfwSetKeyCallback(m_nativeWindow, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*) glfwGetWindowUserPointer(glfwWindow);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent keyPressed = KeyPressedEvent(key, 0);
						data.eventCallback(keyPressed);
						break;
					}

					case GLFW_RELEASE:
					{
						KeyReleasedEvent keyReleased = KeyReleasedEvent(key);
						data.eventCallback(keyReleased);
						break;
					}

					case GLFW_REPEAT:
					{
						KeyPressedEvent keyRepeated = KeyPressedEvent(key, 1);
						data.eventCallback(keyRepeated);
						break;
					}
				}
			}
		);

		// Increment window count.
		++s_WindowCount;
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_nativeWindow);
		--s_WindowCount;

		if (s_WindowCount == 0)
		{
			glfwTerminate();
		}
	}

	//==========| Events |=========//

	void Window::OnUpdate()
	{
		glfwSwapBuffers(m_nativeWindow);
		glfwPollEvents();
	}

	//==========| Setters |==========//

	void Window::SetEventCallback(const std::function<void(Event&)>& clbk)
	{
		m_WindowData.eventCallback = clbk;
	}

	void Window::SetVSync(bool enabled)
	{
		m_WindowData.vsync = enabled;
		glfwSwapInterval((int)enabled);
	}

	//==========| Getters |==========//

	bool Window::IsVSync() const
	{
		return m_WindowData.vsync;
	}

	glm::ivec2 Window::GetPosition() const
	{
		return m_WindowData.position;
	}

	glm::u32vec2 Window::GetSize() const
	{
		return m_WindowData.size;
	}

	GLFWwindow* Window::GetNativeWindow()
	{
		return m_nativeWindow;
	}
}