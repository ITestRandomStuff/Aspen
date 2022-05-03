#include "Application.h"

namespace Aspen
{
	bool Application::m_instanced = false;

	Application::Application(const std::string& title)
	{
		ASP_ASSERT(m_instanced, "Application already instanced!");
		m_instanced = true;
	}

	void Application::Run()
	{
		while (m_running);
	}
}