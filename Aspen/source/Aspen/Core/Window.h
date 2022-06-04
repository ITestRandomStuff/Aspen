#pragma once

#include "Aspen/Math/Vector2.h"
#include "Aspen/Event/Event.h"

struct GLFWwindow;

namespace Aspen
{
	struct WindowData
	{
		std::string title;

		Vector2<uint32_t> size;
		Vector2i position;

		std::function<void(Event&)> eventCallback;
	};

	class Window
	{
	public:
		Window(uint32_t width, uint32_t height, const std::string& title);
		~Window();

		void OnUpdate();

		void SetEventCallback(const std::function<void(Event&)>& clbk);
		void Close();

		GLFWwindow* GetNativeWindow() { return m_NativeWindow; }

	private:
		GLFWwindow* m_NativeWindow;
		WindowData m_WindowData;

		static uint8_t s_WindowCount;
	};
}