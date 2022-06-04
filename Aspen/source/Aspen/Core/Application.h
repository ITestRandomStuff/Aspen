#pragma once

#include "Aspen/Core/Window.h"
#include "Aspen/Event/WindowEvents.h"

#include "Aspen/Core/LayerStack.h"

namespace Aspen
{
	class Application
	{
	public:
		Application(uint32_t width, uint32_t height, const std::string& title);
		~Application();

		void Run();

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& closeEvent);

		static Application& GetApplication() { return *s_Instance; }
		Window& GetWindow() { return *m_Window; }

	private:
		bool m_Running = false;

		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	Application* CreateApplication(uint32_t width = 1080, uint32_t height = 720, const std::string& title = "Application");
}