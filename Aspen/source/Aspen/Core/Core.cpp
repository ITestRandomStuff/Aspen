#include "Aspen/Core/Core.h"

namespace Aspen
{
	void Aspen::ASP_ASSERT(bool condition, const std::string& text)
	{
		if (condition) std::cout << text;
	}
}