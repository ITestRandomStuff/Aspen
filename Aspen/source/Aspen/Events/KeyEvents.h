#pragma once

#include "Events.h"
#include "Aspen/Core/KeyCode.h"

namespace Aspen
{
	class KeyPressedEvent : public Event
	{
	public:
		KeyPressedEvent(const KeyCode key, const uint16_t repeat)
			:m_Key(key), m_RepeatCount(repeat)
		{
		}

		ASP_EVTYPE(EventType::KeyPressed);
		KeyCode GetKey() const
		{
			return m_Key;
		}

		uint16_t GetRepeatCount() const
		{
			return m_RepeatCount;
		}

	private:
		KeyCode m_Key;
		uint16_t m_RepeatCount;
	};

	class KeyReleasedEvent : public Event
	{
	public:
		KeyReleasedEvent(const KeyCode key)
			:m_Key(key)
		{
		}

		ASP_EVTYPE(EventType::KeyReleased);
		KeyCode GetKey() const
		{
			return m_Key;
		}

	private:
		KeyCode m_Key;
	};
}