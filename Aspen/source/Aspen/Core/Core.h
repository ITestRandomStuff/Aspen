#pragma once

// Preprocessor definitions
//#define ASP_SHOW_LOGS

#include "Aspen/Core/Log.h"

#define ASP_ASSERT(condition, ...) if (condition) { ASP_ERROR(__VA_ARGS__); }
#define ASP_CRIT_ASSERT(condition, ...) if (condition) { ASP_CRIT(__VA_ARGS__); }