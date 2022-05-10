#pragma once
#include "Aspen/Core/Window.h"

namespace Aspen
{
	class Application
	{
	public:
		Application(const std::string& title);
		~Application();

		void Run();
		void Destroy();

		void OnUpdate();

	private:
		bool m_running = false;
		std::unique_ptr<Window> m_window;
	};

	Application* CreateApplication(const std::string& title);
}