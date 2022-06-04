#pragma once

#include <stdint.h>
#include "Aspen/Event/Event.h"

namespace Aspen
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t width, uint32_t height)
			:m_Width(width), m_Height(height)
		{
		}

		ASP_EVENTTYPE(EventType::WindowResize);

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

	private:
		uint32_t m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{
		}

		ASP_EVENTTYPE(EventType::WindowClose);
	};
}