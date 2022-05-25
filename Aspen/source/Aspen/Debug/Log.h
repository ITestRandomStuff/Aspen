#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/sinks/ansicolor_sink.h>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

#include <glm/vec2.hpp>

namespace Aspen
{
	class Logger
	{
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetLogger();

	private:
		static std::shared_ptr<spdlog::logger> m_Logger;
	};
}

#if defined(ASP_CONFIG_DEBUG) || defined(ASP_SHOW_LOGS)

#define ASP_LOG(...)	::Aspen::Logger::GetLogger()->trace(__VA_ARGS__)
#define ASP_INFO(...)   ::Aspen::Logger::GetLogger()->info(__VA_ARGS__)
#define ASP_WARN(...)   ::Aspen::Logger::GetLogger()->warn(__VA_ARGS__)

#define ASP_ERROR(...)  ::Aspen::Logger::GetLogger()->error(__VA_ARGS__)
#define ASP_CRIT(...)   ::Aspen::Logger::GetLogger()->critical(__VA_ARGS__); throw

#define ASP_ASSERT(condition, ...)      if (condition) { ASP_ERROR(__VA_ARGS__); }
#define ASP_CRIT_ASSERT(condition, ...) if (condition) { ASP_CRIT(__VA_ARGS__); }

#else

#define ASP_LOG(...) ::Aspen::Logger::GetLogger()->trace(__VA_ARGS__)
#define ASP_INFO(...)
#define ASP_WARN(...)

#define ASP_ERROR(...)
#define ASP_CRIT(...)

#define ASP_ASSERT(condition, ...)
#define ASP_CRIT_ASSERT(condition, ...)

#endif