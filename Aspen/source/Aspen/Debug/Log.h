#pragma once

// Just patched this thing together in a couple of minutes

//#define ASP_LOG_FILENAME 1

#if defined(ASP_LOG_FILENAME)
#include <string.h>

// https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
#define __FILENAME__ strrchr("\\"__FILE__, '\\') + 1
#endif

namespace Aspen
{
	class Logger
	{
	public:
		static void SetName(const std::string& name = "Aspen");
		static void SetColor(const std::string& color);

		static void Trace(const std::string& msg, int line, const std::string filename = "");
		static void Info(const std::string& msg, int line, const std::string filename);
		static void Warn(const std::string& msg, int line, const std::string filename);
		static void Error(const std::string& msg, int line, const std::string filename);
		static void Critical(const std::string& msg, int line, const std::string filename);

		static void Trace(const std::string& msg);
		static void Info(const std::string& msg);
		static void Warn(const std::string& msg);
		static void Error(const std::string& msg);
		static void Critical(const std::string& msg);

	public:
		inline static std::string Red = "\033[31m";
		inline static std::string Yellow = "\033[33m";
		inline static std::string Cyan = "\033[36m";
		inline static std::string White = "\033[37m";

		inline static std::string BoldRed = "\033[31m\033[1m";

	private:
		static std::string m_Name;
		static std::string m_Message;

		static bool s_LogInitialized;
	};
}

//#define ASP_SHOW_LOGS 1

#include "Aspen/Math/Vector2.h"

#if defined(ASP_CONFIG_DEBUG) || defined(ASP_SHOW_LOGS)

#	if defined(ASP_LOG_FILENAME)

#	define ASP_LOG(msg) Logger::Trace(msg, __LINE__, __FILENAME__);
#	define ASP_INFO(msg) Logger::Info(msg, __LINE__, __FILENAME__);

#	define ASP_WARN(msg) Logger::Warn(msg, __LINE__, __FILENAME__);
#	define ASP_ERROR(msg) Logger::Error(msg, __LINE__, __FILENAME__);
#	define ASP_CRIT(msg) Logger::Critical(msg, __LINE__, __FILENAME__);

#	else

#	define ASP_LOG(msg) Logger::Trace(msg);
#	define ASP_INFO(msg) Logger::Info(msg);

#	define ASP_WARN(msg) Logger::Warn(msg);
#	define ASP_ERROR(msg) Logger::Error(msg);
#	define ASP_CRIT(msg) Logger::Critical(msg);

#	endif

#define ASP_ASSERT(condition, msg) if (condition) ASP_ERROR(msg)
#define ASP_CRIT_ASSERT(condition, msg) if (condition) { ASP_CRIT(msg); throw; }

#else

#define ASP_LOG(msg)
#define ASP_INFO(msg)

#define ASP_WARN(msg)
#define ASP_ERROR(msg)
#define ASP_CRIT(msg)

#define ASP_ASSERT(condition, msg)
#define ASP_CRIT_ASSERT(condition, msg)

#endif

template<typename Ty>
inline std::ostream& operator<<(std::ostream &out, const Aspen::Vector2<Ty> &v)
{
	out << "(" << v.x << ", " << v.y << ")";
	return out;
}