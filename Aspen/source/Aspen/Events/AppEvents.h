#pragma once

#include "Events.h"

namespace Aspen
{
	class WindowPositionEvent : public Event
	{
	public:
		WindowPositionEvent(int x, int y) { m_PosX = x;  m_PosY = y; }
		ASP_EVTYPE(EventType::WindowPosition);

		int GetPositionX() const { return m_PosX; }
		int GetPositionY() const { return m_PosY; }

	private:
		int m_PosX;
		int m_PosY;
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint32_t w, uint32_t h) { m_Width = w;  m_Height = h; }
		ASP_EVTYPE(EventType::WindowResize);

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

	private:
		uint32_t m_Width;
		uint32_t m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;
		ASP_EVTYPE(EventType::WindowClose);
	};
}