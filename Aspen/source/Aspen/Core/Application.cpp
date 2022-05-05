#include "aspch.h"
#include "Application.h"

namespace Aspen
{
	bool Application::s_instanced = false;
	bool Application::s_running   = false;

	std::string Application::s_title = "";

	std::vector<std::unique_ptr<Window>> Application::s_windows = {  };

	Application::Application(const std::string& title)
	{
		Log::InitLog();

		ASP_CRIT_ASSERT(s_instanced, "Application already instanced!");
		s_instanced = true;
		s_title = title;
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		s_running = true;
		s_windows.emplace_back(std::make_unique<Window>(640, 480, s_title, "icon.png"));

		while (s_running)
		{
			// Remove window from vector if deleted.
			std::erase_if(s_windows, [](std::unique_ptr<Window>& window)
				{
					return window->IsWindowClosed();
				});

			// Update the windows in vector.
			for (auto& window : s_windows)
			{
				window->OnUpdate();
			}

			// If no windows are open, stop the application from running.
			if (s_windows.size() == 0)
			{
				s_running = false;
			}
		}

	}
}