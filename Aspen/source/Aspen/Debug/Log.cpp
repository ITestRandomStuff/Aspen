#include "aspch.h"
#include "Log.h"

#include <spdlog/sinks/ansicolor_sink.h>

namespace Aspen
{
	std::shared_ptr<spdlog::logger> Log::m_Logger;

	void Log::Init()
	{
		auto sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>(spdlog::color_mode::always);
		sink->set_pattern("%^[%n]: %v%$");

		sink->set_color(spdlog::level::trace,    sink->white);
		sink->set_color(spdlog::level::info,     sink->cyan);

		sink->set_color(spdlog::level::warn,     sink->yellow);
		sink->set_color(spdlog::level::err,      sink->red_bold);
		sink->set_color(spdlog::level::critical, sink->red);

		m_Logger = std::make_shared<spdlog::logger>("Aspen", sink);
		spdlog::register_logger(m_Logger);

		spdlog::set_level(spdlog::level::trace);
		m_Logger->flush_on(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& Log::GetLogger()
	{
		return m_Logger;
	}
}