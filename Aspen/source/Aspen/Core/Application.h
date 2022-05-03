#pragma once
#include "Aspen/Core/Core.h"

namespace Aspen
{
	class Application
	{
	public:
		Application(const std::string& title = "Application");
		virtual ~Application() {  };

		void Run();

	private:
		bool m_running = false;

		static bool m_instanced;
	};
}