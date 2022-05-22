#include "aspch.h"
#include "EventDispatcher.h"

namespace Aspen
{
	using EventCallbackFnc = std::function<void(Event&)>;

	EventDispatcher::EventDispatcher(Event& e)
		:m_Event(e)
	{
	}
}