#include <aspch.h>
#include "Application.h"

#include "Aspen/Debug/Log.h"
#include <glfw/glfw3.h>

namespace Aspen
{
	Application::Application(const std::string& title)
	{
		int glfwInitSuccess = glfwInit();
		if (glfwInitSuccess == GLFW_FALSE)
		{
			ASP_CRIT("Failed to initialize GLFW.");
			return;
		}

		m_window = std::make_unique<Window>(640, 480, title.c_str());
		m_window->SetIcon("source/Aspen/Data/app_icon.png");
	}

	Application::~Application()
	{
		Destroy();
	}

	void Application::Destroy()
	{
		glfwTerminate();
	}

	void Application::Run()
	{
		m_running = true;
		while (m_running && !m_window->IsClosed())
		{
			OnUpdate();
			m_window->OnUpdate();
		}

		m_window.reset();	// Fix GLFW Error 65535
		m_running = false;
	}

	Application* CreateApplication(const std::string& title)
	{
		return new Application(title);
	}
}