#pragma once

// Preprocessor definitions
//#define ASP_SHOW_LOGS

#include "Aspen/Core/Log.h"

#if defined(ASP_CONFIG_DEBUG) || defined(ASP_SHOW_LOGS)

#define ASP_ASSERT(condition, ...) if (condition) { ASP_ERROR(__VA_ARGS__); }
#define ASP_CRIT_ASSERT(condition, ...) if (condition) { ASP_CRIT(__VA_ARGS__); }

#else

#define ASP_ASSERT(condition, ...)
#define ASP_CRIT_ASSERT(condition, ...)

#endif