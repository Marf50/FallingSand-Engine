#pragma once
#include "Core.h"

#include "Window.h"
#include "FallingSandEngine/Core/LayerStack.h"
#include "FallingSandEngine/Events/Events.h"
#include "FallingSandEngine/Events/ApplicationEvents.h"

#include "FallingSandEngine/Core/Timestep.h"

#include "FallingSandEngine/ImGui/ImGuiLayer.h"

namespace FallingSandEngine {

	class FSE_API Application
	{
	public:
		Application(const std::string& name = "Falling Sand Application");
		virtual ~Application();
		
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		void Close();

		template<typename T>
		T* GetLayerByType()
		{
			return m_LayerStack.GetLayerByType<T>();
		}

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		Timestep m_Timestep;
		float m_LastFrameTime = 0.0f;



		std::queue<std::function<void()>> m_PendingLayerModifications;

	private:
		static Application* s_Instance;
		
	};
	//Defined in Client
	Application* CreateApplication();
}


