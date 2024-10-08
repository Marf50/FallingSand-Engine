#pragma once
#include "FallingSandEngine.h"

namespace FallingSandEngine
{
    class DevCameraScript : public ScriptableEntity
    {
    public:
        DevCameraScript(Ref<Scene> activeScene, Ref<ChunkManager> chunkManager)
            : m_ActiveScene(activeScene), m_ChunkManager(chunkManager) {}

        void OnCreate() override
        {
            // Initialize camera movement and any other setup logic here
        }

        void OnUpdate(Timestep ts) override
        {
            // Handle camera movement
            UpdateCameraMovement(ts);

            // Handle cell placement
            UpdateCellPlacement(ts);

            RenderDebugInformation();
        }

    private:
        Ref<Scene> m_ActiveScene;
        Ref<ChunkManager> m_ChunkManager;
        float m_CameraSpeed = 75.0f;

        bool showChunkBoundaries = false;
        bool showDirtyRectangles = false;
        bool showAwakeCells = false;
            

        // Camera movement logic
        void UpdateCameraMovement(Timestep ts)
        {
            auto& transformComponent = GetComponent<TransformComponent>();
            if (Input::IsKeyPressed(KeyCode::W))
                transformComponent.Translation.y += (m_CameraSpeed * ts);

            if (Input::IsKeyPressed(KeyCode::S))
                transformComponent.Translation.y -= (m_CameraSpeed * ts);

            if (Input::IsKeyPressed(KeyCode::A))
                transformComponent.Translation.x -= (m_CameraSpeed * ts);

            if (Input::IsKeyPressed(KeyCode::D))
                transformComponent.Translation.x += (m_CameraSpeed * ts);
        }

        // Cell placement logic
        void UpdateCellPlacement(Timestep ts)
        {
            auto [mouseX, mouseY] = Input::GetMousePosition();
            glm::ivec2 worldCoords = GetWorldPositionFromMouse(mouseX, mouseY);

            auto [chunkEntity, chunkCoords] = m_ChunkManager->GetChunkAtWorldCoords(worldCoords.x, worldCoords.y);
            if (chunkEntity)
            {
                auto& chunkComponent = chunkEntity.GetComponent<ChunkComponent>();

                int relCellX = (worldCoords.x % 64 + 64) % 64;
                int relCellY = (worldCoords.y % 64 + 64) % 64;

                if (relCellX >= 0 && relCellX < 64 && relCellY >= 0 && relCellY < 64)
                {
                    if (Input::IsKeyPressed(KeyCode::D1))
                        PlaceCell(relCellX, relCellY, ElementType::Sand, chunkComponent);
                    if (Input::IsKeyPressed(KeyCode::D2))
                        PlaceCell(relCellX, relCellY, ElementType::Dirt, chunkComponent);
                    if (Input::IsKeyPressed(KeyCode::D3))
                        PlaceCell(relCellX, relCellY, ElementType::Water, chunkComponent);
                    if (Input::IsKeyPressed(KeyCode::D4))
                        PlaceCell(relCellX, relCellY, ElementType::Stone, chunkComponent);
                    if (Input::IsKeyPressed(KeyCode::D5))
                        PlaceCell(relCellX, relCellY, ElementType::Air, chunkComponent);
                }
            }
        }

        glm::ivec2 GetWorldPositionFromMouse(float mouseX, float mouseY)
        {
            auto& cameraComponent = GetComponent<CameraComponent>();
            auto& transformComponent = GetComponent<TransformComponent>();

            glm::mat4 viewMatrix = glm::inverse(glm::translate(glm::mat4(1.0f), transformComponent.Translation) *
                glm::rotate(glm::mat4(1.0f), glm::radians(transformComponent.Rotation.z), glm::vec3(0, 0, 1)));

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



        void RenderDebugInformation()
        {
            Renderer2D::BeginScene(GetComponent<CameraComponent>().Camera, GetComponent<TransformComponent>().GetTransform());


            if (Input::IsKeyPressed(KeyCode::F1))
                showChunkBoundaries = !showChunkBoundaries;
            if (Input::IsKeyPressed(KeyCode::F2))
                showDirtyRectangles = !showDirtyRectangles;
            if (Input::IsKeyPressed(KeyCode::F3))
                showAwakeCells = !showAwakeCells;




            if (showChunkBoundaries)
                RenderChunkBounds();

            if (showDirtyRectangles)
                RenderDirtyRectangles();

            if (showAwakeCells)
                RenderAwakeCells();

            Renderer2D::EndScene();
        }

        // Rendering functions for each debug feature
        void RenderChunkBounds()
        {
            for (auto& [chunkCoords, chunkEntity] : m_ChunkManager->GetChunks())
            {
                if (chunkEntity.HasComponent<ChunkComponent>() && chunkEntity.HasComponent<TransformComponent>()) {
                    auto& chunkComponent = chunkEntity.GetComponent<ChunkComponent>();
                    auto& transformComponent = chunkEntity.GetComponent<TransformComponent>();

                    // Each chunk is 64x64 cells
                    glm::vec3 chunkPosition = transformComponent.Translation + glm::vec3(64 * chunkComponent.ChunkCoords[0], 64 * chunkComponent.ChunkCoords[1], 0.0f);
                    glm::vec2 chunkSize = glm::vec2(64.0f, 64.0f);  // Size of the chunk in cells

                    // Outline thickness
                    float thickness = 0.2f;  // Adjust thickness

                    // Adjust the position of each quad to remove the half-cell offset
                    // Correcting by subtracting 0.5 from x and y for proper grid alignment

                    // Bottom edge
                    Renderer2D::DrawQuad(glm::vec3(chunkPosition.x + chunkSize.x / 2 - 0.5f, chunkPosition.y - thickness / 2 - 0.5f, 0.0f), glm::vec2(chunkSize.x, thickness), glm::vec4(0.0, 0.0, 1.0, 1.0));  // Bottom edge

                    // Top edge
                    Renderer2D::DrawQuad(glm::vec3(chunkPosition.x + chunkSize.x / 2 - 0.5f, chunkPosition.y + chunkSize.y + thickness / 2 - 0.5f, 0.0f), glm::vec2(chunkSize.x, thickness), glm::vec4(0.0, 0.0, 1.0, 1.0));  // Top edge

                    // Left edge
                    Renderer2D::DrawQuad(glm::vec3(chunkPosition.x - thickness / 2 - 0.5f, chunkPosition.y + chunkSize.y / 2 - 0.5f, 0.0f), glm::vec2(thickness, chunkSize.y), glm::vec4(0.0, 0.0, 1.0, 1.0));  // Left edge

                    // Right edge
                    Renderer2D::DrawQuad(glm::vec3(chunkPosition.x + chunkSize.x + thickness / 2 - 0.5f, chunkPosition.y + chunkSize.y / 2 - 0.5f, 0.0f), glm::vec2(thickness, chunkSize.y), glm::vec4(0.0, 0.0, 1.0, 1.0));  // Right edge
                }
            }
        }

        void RenderDirtyRectangles()
        {
            for (auto& [chunkCoords, chunkEntity] : m_ChunkManager->GetChunks())
            {
                if (chunkEntity.HasComponent<ChunkComponent>() && chunkEntity.HasComponent<TransformComponent>()) {
                    auto& chunkComponent = chunkEntity.GetComponent<ChunkComponent>();
                    auto& transformComponent = chunkEntity.GetComponent<TransformComponent>();

                    // Calculate the dirty rectangle dynamically
                    int minX = 63, minY = 63, maxX = 0, maxY = 0;
                    bool hasAwakeCells = false;

                    for (int x = 0; x < 64; ++x)
                    {
                        for (int y = 0; y < 64; ++y)
                        {
                            if (ElementInterface::GetFlag(chunkComponent.Cells[x][y], ElementInterface::AWAKE_FLAG) == true)
                            {
                                if (x < minX) minX = x;
                                if (x > maxX) maxX = x;
                                if (y < minY) minY = y;
                                if (y > maxY) maxY = y;
                                hasAwakeCells = true;
                            }
                        }
                    }

                    if (hasAwakeCells)
                    {
                        glm::vec3 rectPosition = transformComponent.Translation + glm::vec3(minX + (64 * chunkComponent.ChunkCoords[0]), minY + (64 * chunkComponent.ChunkCoords[1]), 0.0f);
                        glm::vec2 rectSize = glm::vec2(maxX - minX + 1, maxY - minY + 1);  // Add +1 to cover the full range of cells

                        // Thickness of the outline
                        float thickness = 0.3f;

                        // Correct the positions with -0.5 offset to align with grid
                        // Bottom edge
                        Renderer2D::DrawQuad(glm::vec3(rectPosition.x + rectSize.x / 2 - 0.5f, rectPosition.y - thickness / 2 - 0.5f, 0.0f), glm::vec2(rectSize.x, thickness), glm::vec4(0.0, 1.0, 0.0, 1));  // Green

                        // Top edge
                        Renderer2D::DrawQuad(glm::vec3(rectPosition.x + rectSize.x / 2 - 0.5f, rectPosition.y + rectSize.y + thickness / 2 - 0.5f, 0.0f), glm::vec2(rectSize.x, thickness), glm::vec4(0.0, 1.0, 0.0, 1));  // Green

                        // Left edge
                        Renderer2D::DrawQuad(glm::vec3(rectPosition.x - thickness / 2 - 0.5f, rectPosition.y + rectSize.y / 2 - 0.5f, 0.0f), glm::vec2(thickness, rectSize.y), glm::vec4(0.0, 1.0, 0.0, 1));  // Green

                        // Right edge
                        Renderer2D::DrawQuad(glm::vec3(rectPosition.x + rectSize.x + thickness / 2 - 0.5f, rectPosition.y + rectSize.y / 2 - 0.5f, 0.0f), glm::vec2(thickness, rectSize.y), glm::vec4(0.0, 1.0, 0.0, 1));  // Green
                    }
                }
            }
        }



        void RenderAwakeCells()
        {
            for (auto& [chunkCoords, chunkEntity] : m_ChunkManager->GetChunks())
            {
                if (chunkEntity.HasComponent<ChunkComponent>() && chunkEntity.HasComponent<TransformComponent>()) {
                    auto& chunkComponent = chunkEntity.GetComponent<ChunkComponent>();
                    auto& transformComponent = chunkEntity.GetComponent<TransformComponent>();

                    for (int x = 0; x < 64; ++x)
                    {
                        for (int y = 0; y < 64; ++y)
                        {
                            if (ElementInterface::GetFlag(chunkComponent.Cells[x][y], ElementInterface::AWAKE_FLAG) == true)
                            {
                                // Calculate the position of the cell
                                glm::vec3 cellPosition = transformComponent.Translation + glm::vec3(x + (64 * chunkComponent.ChunkCoords[0]), y + (64 * chunkComponent.ChunkCoords[1]), 0.0f);

                                // Cell size (assuming 1x1 cells)
                                glm::vec2 cellSize = glm::vec2(1.0f, 1.0f);

                                // Outline thickness
                                float thickness = 0.3f;  // You can adjust the thickness as needed

                                // Correct the position to align with the grid by subtracting 0.5
                                // Bottom edge
                                Renderer2D::DrawQuad(glm::vec3(cellPosition.x + cellSize.x / 2 - 0.5f, cellPosition.y - thickness / 2 - 0.5f, 0.0f), glm::vec2(cellSize.x, thickness), glm::vec4(1.0, 0.0, 0.0, 1.0)); // Bottom edge

                                // Top edge
                                Renderer2D::DrawQuad(glm::vec3(cellPosition.x + cellSize.x / 2 - 0.5f, cellPosition.y + cellSize.y + thickness / 2 - 0.5f, 0.0f), glm::vec2(cellSize.x, thickness), glm::vec4(1.0, 0.0, 0.0, 1.0)); // Top edge

                                // Left edge
                                Renderer2D::DrawQuad(glm::vec3(cellPosition.x - thickness / 2 - 0.5f, cellPosition.y + cellSize.y / 2 - 0.5f, 0.0f), glm::vec2(thickness, cellSize.y), glm::vec4(1.0, 0.0, 0.0, 1.0)); // Left edge

                                // Right edge
                                Renderer2D::DrawQuad(glm::vec3(cellPosition.x + cellSize.x + thickness / 2 - 0.5f, cellPosition.y + cellSize.y / 2 - 0.5f, 0.0f), glm::vec2(thickness, cellSize.y), glm::vec4(1.0, 0.0, 0.0, 1.0)); // Right edge
                            }
                        }
                    }
                }
            }
        }
    };
}