#pragma once

#include <glm/vec2.hpp>

#include "Aspen/Debug/Log.h"
#include "Aspen/Events/EventDispatcher.h"

#include "glfw/glfw3.h"

namespace Aspen
{
	struct WindowData
	{
		glm::ivec2 position;
		glm::u32vec2 size;

		std::string title;
		bool vsync;

		std::function<void(Event&)> eventCallback;
	};

	class Window
	{
	public:
		Window(uint32_t width = 640, uint32_t height = 480, const std::string& title = "Window", bool fullscreen = false);
		~Window();

		void OnUpdate();

		bool IsVSync() const;
		glm::ivec2 GetPosition() const;
		glm::u32vec2 GetSize() const;

		GLFWwindow* GetNativeWindow();

		void SetVSync(bool enabled);
		void SetEventCallback(const std::function<void(Event&)>& clbk);


	private:
		GLFWwindow* m_nativeWindow;

		WindowData m_WindowData;
		static uint8_t s_WindowCount;
	};
}