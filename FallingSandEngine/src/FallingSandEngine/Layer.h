#pragma once
#include "FallingSandEngine/Core.h"
#include "FallingSandEngine/Events/Events.h"

namespace FallingSandEngine
{

	class FSE_API Layer
	{
	public:
		//takes a layer name, if none names the layer "Layer"
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}