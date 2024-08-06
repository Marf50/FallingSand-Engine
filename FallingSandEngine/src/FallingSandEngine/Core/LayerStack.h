#pragma once
#include "FallingSandEngine/Core/Core.h"
#include "Layer.h"

#include <vector>
//maybe define std::vector<layer*> macro

namespace FallingSandEngine
{
	//not actually a stack is a vector so that you can push into the middle
	//raw pointers are owned by the layerstack
	class FSE_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};
}