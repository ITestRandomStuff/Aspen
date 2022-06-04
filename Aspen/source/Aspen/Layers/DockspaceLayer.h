#pragma once

#include "Aspen/Layers/GuiLayer.h"

namespace Aspen
{
	class DockspaceLayer : public GuiLayer
	{
	public:
		virtual void OnRender() override;

		void RenderMenuBar();
		void RenderFileMenuItem();
		void RenderViewMenuItem();
		void RenderSettingsMenuItem();
	};
}