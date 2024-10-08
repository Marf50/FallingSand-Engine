#pragma once
#include "FallingSandEngine.h"

namespace FallingSandEngine
{
	class CellPlacer : public ScriptableEntity
	{
	public:

		CellPlacer(Ref<Scene> activeScene, Ref<ChunkManager> chunkManager)
			:m_ActiveScene(activeScene), m_ChunkManager(chunkManager) {}

		void OnCreate() override
		{

		}
		void OnUpdate(Timestep ts) override
		{
			auto [mouseX, mouseY] = Input::GetMousePosition();
			glm::ivec2 worldCoords = GetWorldPositonFromMouse(mouseX, mouseY);
			auto [chunkEntity, chunkCoords] = m_ChunkManager->GetChunkAtWorldCoords(worldCoords.x, worldCoords.y);
			if (chunkEntity)
			{
				auto& chunkComponent = chunkEntity.GetComponent<ChunkComponent>();

				int relCellX = (worldCoords.x % 64 + 64) % 64;
				int relCellY = (worldCoords.y % 64 + 64) % 64;

				if (relCellX >= 0 && relCellX < 64 && relCellY >= 0 && relCellY < 64)
				{
					//FSE_INFO("Cell coordinates ({0}, {1})  at chunk ({2},{3}) ", relCellX, relCellY, chunkCoordsX, chunkCoordsY);

					if (Input::IsKeyPressed(KeyCode::D1))
					{
						PlaceCell(relCellX, relCellY, ElementType::Sand, chunkComponent);
					}
					if (Input::IsKeyPressed(KeyCode::D2))
					{
						PlaceCell(relCellX, relCellY, ElementType::Dirt, chunkComponent);
					}
					if (Input::IsKeyPressed(KeyCode::D3))
					{
						PlaceCell(relCellX, relCellY, ElementType::Water, chunkComponent);
					}
					if (Input::IsKeyPressed(KeyCode::D4))
					{
						PlaceCell(relCellX, relCellY, ElementType::Stone, chunkComponent);
					}
					if (Input::IsKeyPressed(KeyCode::D5))
					{
						PlaceCell(relCellX, relCellY, ElementType::Air, chunkComponent);
					}

				}
			}
		}

	private:
		Ref<Scene> m_ActiveScene;
		Ref<ChunkManager> m_ChunkManager;


		glm::ivec2 GetWorldPositonFromMouse(float mouseX, float mouseY)
		{
			auto& cameraComponent = GetComponent<CameraComponent>();
			auto& transformComponent = GetComponent<TransformComponent>();

			glm::mat4 viewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), transformComponent.Translation) *
				glm::rotate(glm::mat4(1.0f), glm::radians(transformComponent.Rotation.z), glm::vec3(0, 0, 1)));

			// no way to grab the viewport size from here hmmm idk what ill do about that haha nvm lamda go crazy ig
			glm::vec4 viewport = glm::vec4(0, 0, m_ActiveScene->GetViewportWidth(), m_ActiveScene->GetViewportHeight());
			glm::vec3 worldPosition = cameraComponent.Camera.ScreenToWorld(glm::vec2(mouseX, mouseY), viewMatrix, viewport);

			return glm::ivec2(worldPosition.x, worldPosition.y);
		}

		void PlaceCell(int x, int y, ElementType type, ChunkComponent& chunk)
		{
			ElementInterface::SetElementType(chunk.Cells[x][y], type);
			ElementInterface::SetVelocityX(chunk.Cells[x][y], 0);
			ElementInterface::SetVelocityY(chunk.Cells[x][y], 0);
			ElementInterface::SetFlag(chunk.Cells[x][y], ElementInterface::AWAKE_FLAG, true);
		}
	};
}