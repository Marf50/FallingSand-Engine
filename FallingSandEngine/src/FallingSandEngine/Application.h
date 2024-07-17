#pragma once
#include "Core.h"

#include "Window.h"
#include "FallingSandEngine/LayerStack.h"
#include "FallingSandEngine/Events/Events.h"
#include "FallingSandEngine/Events/ApplicationEvents.h"

#include "FallingSandEngine/ImGui/ImGuiLayer.h"

namespace FallingSandEngine {

	class FSE_API Application
	{
	public:
	Application();
	virtual ~Application();
		
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};
	//Defined in Client
	Application* CreateApplication();
}


