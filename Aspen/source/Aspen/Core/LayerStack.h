#pragma once

#include "Aspen/Core/Layer.h"

namespace Aspen
{
	class LayerStack
	{
		using LayersType = std::vector<Layer*>;

	public:
		LayerStack();
		~LayerStack();

		// For loop
		LayersType::iterator begin() { return m_Layers.begin(); }
		LayersType::iterator end() { return m_Layers.end(); }

		LayersType::reverse_iterator rend() { return m_Layers.rend(); }
		LayersType::reverse_iterator rbegin() { return m_Layers.rbegin(); }

		LayersType::const_iterator begin() const { return m_Layers.begin(); }
		LayersType::const_iterator end() const { return m_Layers.end(); }

		LayersType::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		LayersType::const_reverse_iterator rend() const { return m_Layers.rend(); }

		void PushLayer(Layer* layer);
		void PushLayer(Layer* layer, size_t index);

		bool empty() { return m_Layers.empty(); }

		void PopLayer();
		void PopLayer(size_t index);

	private:
		LayersType m_Layers;
	};
}