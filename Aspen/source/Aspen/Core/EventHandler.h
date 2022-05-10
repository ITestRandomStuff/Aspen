#pragma once

namespace Aspen
{
	class EventHandler
	{
	public:
		template<typename... Fargs, typename... Args>
		static void DispatchEvent(void(*func)(Fargs...), Args... args)
		{
			return func(args...);
		}
	};
}