#pragma once

#include "Aspen/Events/Events.h"

namespace Aspen
{
	// Event dispatcher.
	class EventDispatcher
	{
	public:
		using EventCallbackFnc = std::function<void(Event&)>;

		EventDispatcher(Event& e);

		template<typename Ev, typename Fn>
		void Dispatch(const Fn& clbk)
		{
			if (Ev::GetStaticType() == m_Event.GetType())
				m_Event.handled = clbk(static_cast<Ev&>(m_Event));
		}

	private:
		Event& m_Event;
	};
}