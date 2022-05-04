#include "aspch.h"
#include "Application.h"

namespace Aspen
{
	bool Application::m_instanced = false;

	Application::Application(const std::string& title)
	{
		Log::InitLog();

		ASP_CRIT_ASSERT(m_instanced, "Application already instanced!");
		m_instanced = true;

	}

	void Application::Run()
	{
		m_running = true;
		while (m_running)
		{

		}
	}
}