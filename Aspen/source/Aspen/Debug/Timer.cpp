#include "aspch.h"
#include "Timer.h"

#include <chrono>

namespace Aspen
{
	Timer::Timer()
	{
		m_startTime = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer() { Stop(); }

	void Timer::Stop()
	{
		m_timeElapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now() - m_startTime
		).count();
	}

	float Timer::TimeElapsed() const
	{
		return m_timeElapsed;
	}
}