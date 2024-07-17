#pragma once
#include "FallingSandEngine/Layer.h"
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

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseScrolledEvent(MouseScrollEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);

		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowResizedEvent(WindowResizeEvent& e);
		
	private: 
		float m_Time = 0.0f;
	};
}