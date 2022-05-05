#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/ansicolor_sink.h>

namespace Aspen
{
	class Log
	{
	public:
		static void InitLog();
		static std::shared_ptr<spdlog::logger>& GetLogger();

	private:
		static std::shared_ptr<spdlog::logger> s_logger;
		static bool s_logInit;
	};
}

#if defined(ASP_CONFIG_DEBUG) || defined(ASP_SHOW_LOGS)

#define ASP_LOG(...)    Aspen::Log::GetLogger()->trace(__VA_ARGS__)
#define ASP_INFO(...)   Aspen::Log::GetLogger()->info(__VA_ARGS__)

#define ASP_WARN(...)   Aspen::Log::GetLogger()->warn(__VA_ARGS__)
#define ASP_ERROR(...)  Aspen::Log::GetLogger()->error(__VA_ARGS__)
#define ASP_CRIT(...)   Aspen::Log::GetLogger()->critical(__VA_ARGS__)

#else

#define ASP_LOG(...)
#define ASP_INFO(...)

#define ASP_WARN(...)
#define ASP_ERROR(...)
#define ASP_CRIT(...)

#endif