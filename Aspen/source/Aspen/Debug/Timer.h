#pragma once
#include <chrono>

namespace Aspen
{
	class ScopeTimer
	{
	public:
		ScopeTimer(const std::string& name);
		~ScopeTimer();

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
		std::string m_name;
	};

	class StopTimer
	{
	public:
		StopTimer(const std::string& name);
		~StopTimer();

		void Stop();

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
		std::string m_name;
	};
}

#if defined(ASP_CONFIG_DEBUG)

#define ASP_FUNC_SCTIMER() Aspen::ScopeTimer(__FUNCTION__);
#define ASP_FUNC_TIMER()   Aspen::StopTimer(__FUNCTION__);

#else

#define ASP_FUNC_TIMER()
#define ASP_FUNC_TIMER()

#endif