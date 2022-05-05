#pragma once

#include "Aspen/Core/Core.h"
#include <GLFW/glfw3.h>

namespace Aspen
{
	class Window
	{
	public:
		Window(
			uint32_t width = 640,
			uint32_t height = 480,
			const std::string& title = "Window",
			const std::string& iconPath = "");

		~Window();

		void OnUpdate();

		void OnWindowResize(uint32_t width, uint32_t height);
		void OnWindowReposition(int posX, int posY);
		void OnWindowClose();
		void OnWindowFocus(bool focused);

		bool GetWindowFocus() const;
		void GetWindowSize(uint32_t& width, uint32_t& height) const;
		void GetWindowPosition(int& x, int& y) const;
		bool IsWindowClosed() const;

	private:
		uint32_t m_width;
		uint32_t m_height;

		int m_posX;
		int m_posY;

		std::string m_title;

		GLFWwindow* m_window;
		GLFWmonitor* m_monitor;
		GLFWimage m_icon[1];

		bool m_focused;
		bool m_destroyed = false;

		static uint8_t s_windows;	// Number of windows
	};
}