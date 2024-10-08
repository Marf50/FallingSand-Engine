#include "fsepch.h"
#include "LayerStack.h"

namespace FallingSandEngine
{

	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		m_LayerInsertIndex++;
	}
	//popping layer does not destory, only when full layerstack is destoryed are they destoryed
	//this just removes it from the vector
	void LayerStack::PopLayer(Layer* layer)
	{
		//FSE_CORE_INFO("Popping layer: {0} , LayerInsertIndex before pop; {1}", layer->GetName(), m_LayerInsertIndex);
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
		//FSE_CORE_INFO("LayerInsertIndex after pop: {0}", m_LayerInsertIndex);
	}
	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
			
	}

}