#include "aspch.h"
#include "Log.h"

namespace Aspen
{
	std::shared_ptr<spdlog::logger> Log::s_logger;
	bool Log::s_logInit = false;

	void Log::InitLog()
	{
		if (s_logInit) return;
		s_logInit = true;

		auto sink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>(spdlog::color_mode::always);
		sink->set_pattern("%^[%T] %n: %v%$");	// [23:59:59] Aspen: Hello!

		sink->set_color(spdlog::level::trace, sink->white);
		sink->set_color(spdlog::level::info, sink->cyan);

		sink->set_color(spdlog::level::warn, sink->yellow);
		sink->set_color(spdlog::level::err, sink->red_bold);
		sink->set_color(spdlog::level::critical, sink->red);

		s_logger = std::make_shared<spdlog::logger>("Aspen", sink);
		spdlog::register_logger(s_logger);
		s_logger->set_level(spdlog::level::trace);
	}

	std::shared_ptr<spdlog::logger>& Log::GetLogger()
	{
		return s_logger;
	}
}