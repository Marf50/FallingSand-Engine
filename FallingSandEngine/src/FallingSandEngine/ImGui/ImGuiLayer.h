#pragma once
#include "FallingSandEngine/Core/Layer.h"
#include "FallingSandEngine/Events/ApplicationEvents.h"
#include "FallingSandEngine/Events/KeyEvents.h"
#include "FallingSandEngine/Events/MouseEvents.h"
namespace FallingSandEngine
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
	
		~ImGuiLayer();

		virtual void OnEvent(Event& e) override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
		void SetBlockEvents(bool block) { m_BlockEvents = block; }
		void SetDarkThemeColors();
	private: 
		

		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}