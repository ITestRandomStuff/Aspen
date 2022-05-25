#pragma once

#include "Aspen/Core/Window.h"
#include "Aspen/Events/AppEvents.h"
#include "Aspen/Events/KeyEvents.h"

#include "Aspen/Core/LayerStack.h"

namespace Aspen
{
	class Application
	{
	public:
		Application(
			uint32_t width = 640, uint32_t height = 480,
			const std::string& title = "App");

		~Application();

		void OnEvent(Event& e);

		bool OnWindowResize(WindowResizeEvent& e);
		bool OnWindowPosition(WindowPositionEvent& e);
		bool OnWindowClose(WindowCloseEvent& e);

		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);

		static Application& GetApplication();
		Window& GetWindow();

		void Run();

	private:
		bool m_Running = false;
		std::unique_ptr<Window> m_Window;

		LayerStack m_LayerStack;
		float m_LastFrameTime;

		static Application* s_Instance;	// To get our instance of the application.
	};

	Application* CreateApplication(
		uint32_t width = 640, uint32_t height = 480,
		const std::string& title = "App");
}