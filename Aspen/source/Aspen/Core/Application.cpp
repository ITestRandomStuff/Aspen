#include "aspch.h"
#include "Application.h"

#include "Aspen/Debug/Log.h"
#include <glad/glad.h>

#include "Aspen/Layers/GuiLayer.h"

#include "Aspen/Layers/DockspaceLayer.h"
#include "Aspen/Layers/EditorLayer.h"

namespace Aspen
{
	Application* Application::s_Instance = nullptr;

	Application::Application(uint32_t width, uint32_t height, const std::string& title)
	{
		Log::Init();
		
		ASP_CRITICAL_ASSERT(s_Instance, "Application already exists.");
		s_Instance = this;

		// Create a window.
		m_Window = std::make_unique<Window>(width, height, title);
		m_Window->SetEventCallback([&](Event& e) { OnEvent(e); });

		// Add dockspace? temporary
		m_LayerStack.PushLayer(new DockspaceLayer());
		m_LayerStack.PushLayer(new EditorLayer());
		//m_LayerStack.PushLayer(new CanvasLayer("source/Aspen/Assets/app_icon.png"));
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher = EventDispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>( ASP_BIND_EVENT(Application::OnWindowClose) );
	}

	bool Application::OnWindowClose(WindowCloseEvent& closeEvent)
	{
		m_Running = false;

		return true;
	}

	void Application::Run()
	{
		m_Running = true;
		while (m_Running)
		{
			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Update Layers.
			for (auto& layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			// Render Layers.
			bool empty = m_LayerStack.empty();
			if (!empty)
				GuiLayer::OnRenderBegin();

			for (auto& layer : m_LayerStack)
			{
				layer->OnRender();
			}

			if (!empty)
				GuiLayer::OnRenderEnd();

			// Update window.
			m_Window->OnUpdate();
		}
	}

	Application* CreateApplication(uint32_t width, uint32_t height, const std::string& title)
	{
		return new Application(width, height, title);
	}
}