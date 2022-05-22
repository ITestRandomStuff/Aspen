#pragma once

#include "Aspen/Math/Vector2.h"
#include "Aspen/Events/EventDispatcher.h"

#include "glfw/glfw3.h"

namespace Aspen
{
	struct WindowData
	{
		Vector2i position;
		Vector2<uint32_t> size;

		std::string title;
		bool vsync;

		std::function<void(Event&)> eventCallback;
	};

	class Window
	{
	public:
		Window(uint32_t width = 640, uint32_t height = 480, const std::string& title = "Window");
		~Window();

		void OnUpdate();

		bool IsVSync() const;
		Vector2i GetPosition() const;
		Vector2<uint32_t> GetSize() const;

		GLFWwindow* GetNativeWindow();

		void SetVSync(bool enabled);
		void SetEventCallback(const std::function<void(Event&)>& clbk);


	private:
		GLFWwindow* m_nativeWindow;

		WindowData m_WindowData;
		static uint8_t s_WindowCount;
	};
}