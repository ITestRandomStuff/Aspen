#pragma once

#include "Aspen/Events/Events.h"

namespace Aspen
{
	class Layer
	{
	public:
		Layer();

		virtual void OnAttach() = 0;
		virtual void OnDetach() = 0;

		virtual void OnEvent(Event& e) = 0;
		virtual void OnUpdate(float ts) = 0;
	};
}