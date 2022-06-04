#include "aspch.h"
#include "LayerStack.h"

namespace Aspen
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (auto& layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		m_Layers.emplace_back(layer);
	}

	void LayerStack::PushLayer(Layer* layer, size_t index)
	{
		layer->OnAttach();
		m_Layers.emplace(m_Layers.begin() + index, layer);
	}

	void LayerStack::PopLayer()
	{
		m_Layers[m_Layers.size() - 1]->OnDetach();
		m_Layers.erase(m_Layers.end());
	}

	void LayerStack::PopLayer(size_t index)
	{
		m_Layers[m_Layers.size() - 1]->OnDetach();
		m_Layers.erase(m_Layers.begin() + index);
	}
}