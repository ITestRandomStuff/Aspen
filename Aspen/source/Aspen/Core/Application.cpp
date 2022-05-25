#include "aspch.h"
#include "Application.h"

#include "Aspen/Debug/Log.h"
#include "Aspen/ImGui/GuiLayer.h"

#include "glad/glad.h"

namespace Aspen
{
	Application* Application::s_Instance = nullptr;

	Application::Application(
		uint32_t width, uint32_t height, const std::string& title)
	{
		Logger::Init();

		ASP_ASSERT(s_Instance, "An instance of the application already exists.");
		s_Instance = this;

		m_Window = std::make_unique<Window>(width, height, title, false);
		m_Window->SetEventCallback( ASP_BIND_EVENT(OnEvent) );

		m_LayerStack.PushLayer(new GuiLayer());
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher{ e };
		dispatcher.Dispatch<WindowResizeEvent>(ASP_BIND_EVENT(OnWindowResize));
		dispatcher.Dispatch<WindowPositionEvent>(ASP_BIND_EVENT(OnWindowPosition));
		dispatcher.Dispatch<WindowCloseEvent>(ASP_BIND_EVENT(OnWindowClose));

		dispatcher.Dispatch<KeyPressedEvent>(ASP_BIND_EVENT(OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(ASP_BIND_EVENT(OnKeyReleased));
	}

	bool Application::OnWindowResize(WindowResizeEvent& resizeEvent)
	{
		//ASP_LOG("Window resized!");
		return true;
	}

	bool Application::OnWindowPosition(WindowPositionEvent& posEvent)
	{
		//ASP_LOG("Window changed positions.");
		return true;
	}

	bool Application::OnWindowClose(WindowCloseEvent& closeEvent)
	{
		//ASP_LOG("Window closed.");
		m_Running = false;

		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& pressedEvent)
	{
		//ASP_LOG("Key Pressed: {0}", pressedEvent.GetKey());
		return true;
	}

	bool Application::OnKeyReleased(KeyReleasedEvent& releasedEvent)
	{
		//ASP_LOG("Key Pressed: {0}", releasedEvent.GetKey());
		return true;
	}

	Application& Application::GetApplication()
	{
		return *s_Instance;
	}

	Window& Application::GetWindow()
	{
		return *m_Window;
	}

	void Application::Run()
	{
		m_Running = true;
		while (m_Running)
		{
			float time = (float) glfwGetTime();
			float ts = time - m_LastFrameTime;
			m_LastFrameTime = time;
			
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate(ts);
			}

			m_Window->OnUpdate();
		}
	}

	Application* CreateApplication(
		uint32_t width, uint32_t height, const std::string& title)
	{
		return new Application(width, height, title);
	}
}