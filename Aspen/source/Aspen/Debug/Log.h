#pragma once

#include <chrono>
#include <iostream>

#ifdef ASP_CONFIG_DEBUG

#define ASP_LOG_CLR(msg, clr) std::cout << clr << "[=] Aspen: " << msg << "\033[37m" << '\n';

#define ASP_LOG(msg) std::cout << "[=] Aspen: " << msg << '\n'
#define ASP_INFO(msg) ASP_LOG_CLR(msg, "\033[36m")

#define ASP_WARN(msg) ASP_LOG_CLR(msg, "\033[33m")
#define ASP_ERROR(msg) ASP_LOG_CLR(msg, "\033[31m\033[1m")
#define ASP_CRIT(msg) ASP_LOG_CLR(msg, "\033[31m")

#define ASP_ASSERT(condition, msg) if (condition) ASP_ERROR(msg)
#define ASP_CRIT_ASSERT(condition, msg) if (condition) ASP_CRIT(msg)

#else

#define ASP_LOG(msg)
#define ASP_INFO(msg)

#define ASP_WARN(msg)
#define ASP_ERROR(msg)
#define ASP_CRIT(msg)

#define ASP_ASSERT(condition, msg)
#define ASP_CRIT_ASSERT(condition, msg)

#endif