#pragma once
#include "FallingSandEngine/Core/Layer.h"
#include "FallingSandEngine/Events/ApplicationEvents.h"
#include "FallingSandEngine/Events/KeyEvents.h"
#include "FallingSandEngine/Events/MouseEvents.h"
namespace FallingSandEngine
{
	class FSE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
	
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private: 
		float m_Time = 0.0f;
	};
}