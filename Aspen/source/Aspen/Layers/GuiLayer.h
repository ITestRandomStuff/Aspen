#pragma once

#include "Aspen/Core/Layer.h"

namespace Aspen
{
	class GuiLayer : public Layer
	{
	public:
		GuiLayer();
		virtual ~GuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		static void OnRenderBegin();
		static void OnRenderEnd();

		void SetDarkThemeColors();

	private:
		static bool s_ImGuiInitialized;
	};
}