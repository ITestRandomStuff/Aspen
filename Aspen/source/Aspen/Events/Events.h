#pragma once

#define ASP_BIND_EVENT(fnc) [&](auto&&... args) -> decltype(auto) { return fnc(std::forward<decltype(args)>(args)...); }
#define ASP_EVTYPE(type) EventType GetType() const override { return type; }\
						 static EventType GetStaticType() { return type; }

namespace Aspen
{
	enum class EventType
	{
		WindowResize,
		WindowPosition,
		WindowClose,

		KeyPressed,
		KeyReleased
	};

	// Base Event class.
	class Event
	{
	public:
		virtual ~Event() = default;
		virtual EventType GetType() const = 0;

		bool handled = false;
	};
}