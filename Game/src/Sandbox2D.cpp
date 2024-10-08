#include "Sandbox2D.h"
#include "imgui/imgui.h"
#include <glm/gtc/type_ptr.hpp>
#include "FallingSandEngine/Utils/PlatformUtils.h"
#include "Elements/ElementFactory.h"
namespace FallingSandEngine
{
	Sandbox2D::Sandbox2D()
		:Layer("SandBox2D")
	{
	}

	void Sandbox2D::OnAttach()
	{
		// Loading Stuff
		SettingsManager::SetApplyCallback([this]() {this->OnSettingsUpdate(); });

		// Frame Buffer
		{

		}
		//Scene
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->ResizeBounds(Application::Get().GetWindow().GetWidth(), Application::Get().GetWindow().GetHeight());
		}

		// Basic Entity loader
		{


			

			m_MainCamera = m_ActiveScene->CreateEntity("Camera");
			m_MainCamera.GetComponent<TransformComponent>().Translation = glm::vec3(35, 35, 0);
			auto& cameraComponent = m_MainCamera.AddComponent<CameraComponent>();
			cameraComponent.Camera.SetOrthographic(150.0f, -1.0f, 1.0f);
			cameraComponent.Primary = true;
			//m_MainCamera.AddComponent<NativeScriptComponent>().Bind<FreeCam>();
			m_ChunkManager = CreateRef<ChunkManager>(m_ActiveScene, m_MainCamera, 1);
		}
			m_MainCamera.AddComponent<NativeScriptComponent>().Bind<DevCameraScript>(m_ActiveScene, m_ChunkManager);
			
	}

	void Sandbox2D::OnDetach()
	{
		m_ChunkManager->~ChunkManager();
		m_ActiveScene->~Scene();
		
		
		delete this;
	}

	void Sandbox2D::OnUpdate(Timestep ts)
	{
		// Update
		//FSE_INFO("ts = {0}", ts.GetMilliseconds());
		m_ChunkManager->UpdateChunks();
		// Render
		{
			Renderer2D::ResetStats();
			// Pre Render
			{

				RenderCommand::SetClearColor({ 0.1, 0.1, 0.1, 1 });
				RenderCommand::Clear();
			}

			m_ActiveScene->OnUpdate(ts);
		}
	}

	void Sandbox2D::OnSettingsUpdate()
	{
		m_ChunkManager->SetChunkLoadRadius(SettingsManager::GetSetting<float>("ChunkRenderDistance"));
		m_MainCamera.GetComponent<CameraComponent>().Camera.SetOrthographic(SettingsManager::GetSetting<float>("CameraZoom"), -1.0f, 1.0f);
	}

	void Sandbox2D::OnEvent(Event& e)
	{
		
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(FSE_BIND_EVENT_FN(Sandbox2D::OnKeyPressed));
		dispatcher.Dispatch<WindowResizeEvent>(FSE_BIND_EVENT_FN(Sandbox2D::OnWindowResize));
		dispatcher.Dispatch<MouseButtonPressedEvent>(FSE_BIND_EVENT_FN(Sandbox2D::OnMouseClicked));
	}
	bool Sandbox2D::OnKeyPressed(KeyPressedEvent& e)
	{

		if (e.GetKeyCode() == KeyCode::L) // Press "L" to list all entities
			m_ActiveScene->ListAllEntitesAndComponents();
		if (e.GetKeyCode() == KeyCode::Escape)
		{
			Application::Get().PushOverlay(new EscMenuUILayer());
			return true;
		}


		
		
		return false;
	}
	bool Sandbox2D::OnWindowResize(WindowResizeEvent& e)
	{
		m_ActiveScene->ResizeBounds(e.GetWidth(), e.GetHeight());
		
		return true;
	}
	bool Sandbox2D::OnMouseClicked(MouseButtonPressedEvent& e)
	{
		return false;
	}
}
