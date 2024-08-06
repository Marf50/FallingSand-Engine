#include "fsepch.h"
#include "Application.h"

#include "FallingSandEngine/Renderer/Renderer.h"
#include "Input.h"
#include "FallingSandEngine/Core/Log.h"

#include <GLFW/glfw3.h>


namespace FallingSandEngine
{

#define BIND_EVENT_FN(x) std::bind(&x, this , std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	Application::~Application()
	{
		FSE_PROFILE_FUNCTION();
	}
	Application::Application(const std::string& name)
	{
		FSE_PROFILE_FUNCTION();
		FSE_CORE_ASSERT(!s_Instance, "Application already exists!")
			s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create(WindowProps(name)));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


	}

	void Application::Run()
		{
		FSE_PROFILE_FUNCTION();
			while (m_Running)
			{
				FSE_PROFILE_SCOPE("RunLoop")

				float time = (float)glfwGetTime(); // move to platform Platform::GetTime()
				Timestep timestep = time - m_LastFrameTime;
				m_LastFrameTime = time;
				if (!m_Minimized)
				{
					FSE_PROFILE_SCOPE("LayerStack OnUpdate")
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
				//will go to render thread, todo
				m_ImGuiLayer->Begin();
				{
					FSE_PROFILE_SCOPE("LayerStack OnImguiRender")
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();
				

				m_Window->OnUpdate();

			}
		}

	void Application::Close()
	{
		m_Running = false;
	}

	//if user presses close on window stop running
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		FSE_PROFILE_FUNCTION();
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
	void Application::PushLayer(Layer * layer)
		{
		FSE_PROFILE_FUNCTION();
			m_LayerStack.PushLayer(layer);
			layer->OnAttach();
		}
	void Application::PushOverlay(Layer * layer)
		{
		FSE_PROFILE_FUNCTION();
			m_LayerStack.PushOverlay(layer);
			layer->OnAttach();
		}
	void Application::OnEvent(Event & e)
		{
		FSE_PROFILE_FUNCTION();
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
			dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

			//FSE_CORE_TRACE("{0}",e.ToString()); 
			//should be able to work without having to call .ToString but doesnt, operator might be broken? idk

			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
			{
				(*--it)->OnEvent(e);
				if (e.Handled())
					break;
			}
		}
}
