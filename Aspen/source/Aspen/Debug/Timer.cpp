#include <aspch.h>
#include "Timer.h"

//#include "Aspen/Debug/Log.h"

namespace Aspen
{
	ScopeTimer::ScopeTimer(const std::string& name)
	{
		m_start = std::chrono::high_resolution_clock::now();
		m_name = name;
	}

	ScopeTimer::~ScopeTimer()
	{
		auto us = std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now() - m_start
		).count() * 1.0f;

		//ASP_LOG("{0}, {1} microseconds", m_name, us);
	}


	StopTimer::StopTimer(const std::string& name)
	{
		m_start = std::chrono::high_resolution_clock::now();
		m_name = name;
	}

	StopTimer::~StopTimer()
	{
	}

	void StopTimer::Stop()
	{
		auto us = std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::high_resolution_clock::now() - m_start
			).count() * 1.0f;

		//ASP_LOG("{0}, {1} microseconds", m_name, us);
	}
}