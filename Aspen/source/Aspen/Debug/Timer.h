#pragma once

namespace Aspen
{
	class Timer
	{
	public:
		Timer();
		~Timer();

		void Stop();
		float TimeElapsed() const;

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
		float m_timeElapsed;
	};
}