#pragma once

#include "Aspen/Core/Layer.h"

namespace Aspen
{
	class GuiLayer : public Layer
	{
	public:
		GuiLayer();
		~GuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void OnEvent(Event& e) override;
		void OnUpdate(float ts) override;
	};
}