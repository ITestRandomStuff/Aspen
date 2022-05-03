#pragma once
#include <string>
#include <iostream>

namespace Aspen
{
	// Turn into macro, and use spdlog?
	void ASP_ASSERT(bool condition, const std::string& text);
}