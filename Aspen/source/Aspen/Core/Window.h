#pragma once

#include <glfw/glfw3.h>

namespace Aspen
{
	class Window
	{
	public:
		Window(uint32_t width, uint32_t height, const std::string& title);
		~Window();

		void CloseWindow();

		//======| Events |======//

		void OnUpdate();
		
		void OnWindowResize(uint32_t width, uint32_t height);
		void OnWindowPosition(int posx, int posy);
		void OnWindowClose();
		void OnWindowFocus(bool focused);

		void OnWindowIconify(bool iconified);
		void OnWindowMaximize(bool maximized);


		//======| Getters |======//

		void GetWindowSize(uint32_t& width, uint32_t height);
		void GetWindowPosition(int& posx, int& posy);

		bool IsFocused();
		bool IsClosed();

		//======| Setters |======//
		// The icon path is relative to the visual studio project (.vcxproj) file.
		void SetIcon(const std::string& iconPath);

	private:
		uint32_t m_width, m_height;
		int m_posx, m_posy;

		bool m_focused;
		bool m_destroyed = false;
		std::string m_title;

		GLFWwindow* m_nativeWindow;
		GLFWimage m_icon[1];
	};
}