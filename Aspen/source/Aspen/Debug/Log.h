#pragma once

#include <spdlog/spdlog.h>

namespace Aspen
{
	class Log
	{
	public:
		static void Init();
		static std::shared_ptr<spdlog::logger>& GetLogger();

	private:
		static std::shared_ptr<spdlog::logger> m_Logger;
	};
}

#if defined(ASP_CONFIG_DEBUG)

#define ASP_LOG(...)      ::Aspen::Log::GetLogger()->trace(__VA_ARGS__)
#define ASP_INFO(...)     ::Aspen::Log::GetLogger()->info(__VA_ARGS__)

#define ASP_WARN(...)	  ::Aspen::Log::GetLogger()->warn(__VA_ARGS__)
#define ASP_ERROR(...)    ::Aspen::Log::GetLogger()->error(__VA_ARGS__)
#define ASP_CRITICAL(...) ::Aspen::Log::GetLogger()->critical(__VA_ARGS__); throw

#define ASP_ASSERT(condition, ...) if (condition) { ASP_ERROR(__VA_ARGS__); }
#define ASP_CRITICAL_ASSERT(condition, ...) if (condition) { ASP_CRITICAL(__VA_ARGS__); }

#else

#define ASP_LOG(...)
#define ASP_INFO(...)

#define ASP_WARN(...)
#define ASP_ERROR(...)
#define ASP_CRITICAL(...)

#define ASP_ASSERT(condition, ...)
#define ASP_CRITICAL_ASSERT(condition, ...)

#endif