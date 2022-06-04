#pragma once

#define ASP_EVENTTYPE(type) static EventType GetStaticType() { return type; } \
							EventType GetType() { return type; }

#define ASP_BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Aspen
{
	enum EventType
	{
		WindowClose,
		WindowResize,
		WindowPosition
	};

	class Event
	{
	public:
		virtual ~Event() {};
		
		virtual EventType GetType() = 0;
		bool IsHandled() { return m_Handled; }

		void SetHandled(bool handled) { m_Handled = handled; }

	protected:
		bool m_Handled;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e)
			:m_Event(e)
		{
		}

		template<typename Ev, typename Fn>
		bool Dispatch(const Fn& fn)
		{
			if (Ev::GetStaticType() == m_Event.GetType())
			{
				m_Event.SetHandled( fn(static_cast<Ev&>(m_Event)) );
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
}