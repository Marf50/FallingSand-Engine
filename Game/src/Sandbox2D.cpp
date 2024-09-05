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

		// Frame Buffer
		{

		}
		//Scene
		{
			m_ActiveScene = CreateRef<Scene>();
			m_ActiveScene->ResizeBounds(1280, 720);
		}

		// Basic Entity loader
		{


			

			m_MainCamera = m_ActiveScene->CreateEntity("Camera");
			m_MainCamera.GetComponent<TransformComponent>().Translation = glm::vec3(35, 35, 0);
			auto& cameraComponent = m_MainCamera.AddComponent<CameraComponent>();
			cameraComponent.Camera.SetOrthographic(500.0f, -1.0f, 1.0f);
			cameraComponent.Primary = true;

			m_ChunkManager = CreateRef<ChunkManager>(m_ActiveScene, m_MainCamera, 2);
		}
	}

	void Sandbox2D::OnDetach()
	{
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
		





		auto [mousex, mousey] = Input::GetMousePosition();

		auto& cameraComponent = m_MainCamera.GetComponent<CameraComponent>();
		auto& transformComponent = m_MainCamera.GetComponent<TransformComponent>();
		glm::mat4 viewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), transformComponent.Translation) *
			glm::rotate(glm::mat4(1.0f), glm::radians(transformComponent.Rotation.z), glm::vec3(0, 0, 1)));

		glm::vec4 viewport = glm::vec4(0, 0, m_ActiveScene->GetViewportWidth(), m_ActiveScene->GetViewportHeight());

		glm::vec3 worldPosition = cameraComponent.Camera.ScreenToWorld(glm::vec2(mousex, mousey), viewMatrix, viewport);

		int cellX = static_cast<int>(worldPosition.x);
		int cellY = static_cast<int>(worldPosition.y);
		auto [chunkEntity, chunkCoords] = m_ChunkManager->GetChunkAtWorldCoords(cellX, cellY);
		if (chunkEntity)
		{
			auto& chunkComponent = chunkEntity.GetComponent<ChunkComponent>();

			int chunkCoordsX = chunkCoords.first;
			int chunkCoordsY = chunkCoords.second;
			
			int relCellX = (cellX % 64 + 64) % 64;
			int relCellY = (cellY % 64 + 64) % 64;
			
			if (relCellX >=0 && relCellX < 64 && relCellY >= 0 && relCellY < 64)
			{
				FSE_INFO("Cell coordinates ({0}, {1})  at chunk ({2},{3}) ", relCellX, relCellY, chunkCoordsX, chunkCoordsY);

				if (e.GetKeyCode() == KeyCode::D1) 
				{
					ElementInterface::SetElementType(chunkComponent.Cells[relCellX][relCellY], ElementType::Sand);
					ElementInterface::SetVelocityX(chunkComponent.Cells[relCellX][relCellY], 0);
					ElementInterface::SetVelocityY(chunkComponent.Cells[relCellX][relCellY], 0);
					ElementInterface::SetFlag(chunkComponent.Cells[relCellX][relCellY], ElementInterface::AWAKE_FLAG, true);

				}
				if (e.GetKeyCode() == KeyCode::D2)
				{
					ElementInterface::SetElementType(chunkComponent.Cells[relCellX][relCellY], ElementType::Dirt);
					ElementInterface::SetVelocityX(chunkComponent.Cells[relCellX][relCellY], 0);
					ElementInterface::SetVelocityY(chunkComponent.Cells[relCellX][relCellY], 0);
					ElementInterface::SetFlag(chunkComponent.Cells[relCellX][relCellY], ElementInterface::AWAKE_FLAG, true);
				}
				if (e.GetKeyCode() == KeyCode::D3)
				{
					ElementInterface::SetElementType(chunkComponent.Cells[relCellX][relCellY], ElementType::Water);
					ElementInterface::SetVelocityX(chunkComponent.Cells[relCellX][relCellY], 0);
					ElementInterface::SetVelocityY(chunkComponent.Cells[relCellX][relCellY], 0);
					ElementInterface::SetFlag(chunkComponent.Cells[relCellX][relCellY], ElementInterface::AWAKE_FLAG, true);
				}
				if (e.GetKeyCode() == KeyCode::D4)
				{
					ElementInterface::SetElementType(chunkComponent.Cells[relCellX][relCellY], ElementType::Stone);
					ElementInterface::SetVelocityX(chunkComponent.Cells[relCellX][relCellY], 0);
					ElementInterface::SetVelocityY(chunkComponent.Cells[relCellX][relCellY], 0);
					ElementInterface::SetFlag(chunkComponent.Cells[relCellX][relCellY], ElementInterface::AWAKE_FLAG, true);
				}
				if (e.GetKeyCode() == KeyCode::D5) 
				{
					ElementInterface::SetElementType(chunkComponent.Cells[relCellX][relCellY], ElementType::Air);
					ElementInterface::SetVelocityX(chunkComponent.Cells[relCellX][relCellY], 0);
					ElementInterface::SetVelocityY(chunkComponent.Cells[relCellX][relCellY], 0);
					ElementInterface::SetFlag(chunkComponent.Cells[relCellX][relCellY], ElementInterface::AWAKE_FLAG, true);
				}
				
			}
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
