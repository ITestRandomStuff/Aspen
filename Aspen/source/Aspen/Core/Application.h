#pragma once
#include "Aspen/Core/Core.h"
#include "Aspen/Core/Window.h"

namespace Aspen
{
	class Application
	{
	public:
		Application(const std::string& title = "Application");
		~Application();

		void Run();

	private:
		static bool s_instanced;
		static bool s_running;

		static std::string s_title;

		static std::vector<std::unique_ptr<Window>> s_windows;
	};
}