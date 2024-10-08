#include "ChunkManager.h"
#include "ChunkBehavior.h"
#include "AssetManagement/SettingsManager.h"
#include "NoiseFunctions.h"

namespace FallingSandEngine {

    ChunkManager::ChunkManager(Ref<Scene> activeScene, Entity playerEntity, int chunkLoadRadius)
        : m_ActiveScene(activeScene), m_PlayerEntity(playerEntity), m_ChunkLoadRadius(chunkLoadRadius) {}

    void ChunkManager::Setup(Ref<Scene> activeScene, Entity playerEntity, int chunkLoadRadius)
    {
        m_ActiveScene = activeScene;
        m_PlayerEntity = playerEntity;
        m_ChunkLoadRadius = chunkLoadRadius;
    }

    ChunkManager::~ChunkManager() {
         //Unload all chunks safely by iterating over the map directly
        std::vector<std::pair<int, int>> chunksToUnload;
        for (const auto& [chunkCoords, entity] :m_LoadedChunks) {
            chunksToUnload.push_back(chunkCoords);
        }

        for (const auto& chunk : chunksToUnload)
        {
            UnloadChunk(chunk.first, chunk.second);
        }
        m_LoadedChunks.clear();
    }

    std::unordered_map<std::pair<int, int>, Entity, PairHash>& ChunkManager::GetChunks()
    {
        return m_LoadedChunks;
    }

    void ChunkManager::UpdateChunks() {
        auto [playerChunkX, playerChunkY] = GetPlayerChunkCoords();

        // Check all chunks within the load radius
        for (int dx = -m_ChunkLoadRadius; dx <= m_ChunkLoadRadius; ++dx) {
            for (int dy = -m_ChunkLoadRadius; dy <= m_ChunkLoadRadius; ++dy) {
                int chunkX = playerChunkX + dx;
                int chunkY = playerChunkY + dy;
                std::pair<int, int> chunkCoords = { chunkX, chunkY };

                // Load the chunk if it's not already loaded
                if (m_LoadedChunks.find(chunkCoords) == m_LoadedChunks.end()) {
                    LoadChunk(chunkX, chunkY);
                    FSE_INFO("Loading new Chunk {0} {1}", chunkX, chunkY);
                }
            }
        }

        // Unload chunks that are out of the load radius
        std::vector<std::pair<int, int>> chunksToUnload;
        for (const auto& [coords, entity] : m_LoadedChunks) {
            int dx = coords.first - playerChunkX;
            int dy = coords.second - playerChunkY;
            if (abs(dx) > m_ChunkLoadRadius || abs(dy) > m_ChunkLoadRadius) {
                chunksToUnload.push_back(coords);
            }
        }
        for (auto& coords : chunksToUnload) {
            UnloadChunk(coords.first, coords.second);
        }
    }

    std::pair<int, int> ChunkManager::GetPlayerChunkCoords() {
        auto& playerTransform = m_PlayerEntity.GetComponent<TransformComponent>();
        int playerX = static_cast<int>(playerTransform.Translation.x);
        int playerY = static_cast<int>(playerTransform.Translation.y);
        return { playerX / 64, playerY / 64 }; // Assuming each chunk is 64x64 cells
    }

    void ChunkManager::LoadChunk(int chunkX, int chunkY) {
        // Check if the chunk is already saved (pseudo-function LoadChunkFromStorage for illustration)
        //if (ChunkExistsInStorage(chunkX, chunkY)) {
        //    // Load the chunk from storage
        //    Entity chunk = LoadChunkFromStorage(chunkX, chunkY);  // Load from disk or memory
        //
        //    auto& chunkComponent = chunk.GetComponent<ChunkComponent>();
        //    chunkComponent.ChunkCoords[0] = chunkX;
        //    chunkComponent.ChunkCoords[1] = chunkY;
        //    chunkComponent.IsAwake = true;
        //
        //    m_LoadedChunks[{chunkX, chunkY}] = chunk;  // Add to the loaded chunks map
        //
        //    // Populate neighbors for the loaded chunk (existing logic)
        //    PopulateNeighborsForChunk(chunk, chunkX, chunkY);
        //}
        //else {
            // Generate a new chunk if it doesn't exist
            GenerateNewChunk(chunkX, chunkY);
        //}
    }

    void ChunkManager::UnloadChunk(int chunkX, int chunkY) {
        auto it = m_LoadedChunks.find({ chunkX, chunkY });
        if (it != m_LoadedChunks.end()) {
            if (!it->second.HasComponent<ChunkComponent>()) {
                //FSE_ERROR("Entity does not have a ChunkComponent!");
                return;
            }
            auto& chunkComponent = it->second.GetComponent<ChunkComponent>();
            FSE_INFO("Unloading chunk ({0}, {1})", chunkX, chunkY);
            // Clean up neighbors' pointers to this chunk
            for (int i = 0; i < 8; ++i) {
                if (chunkComponent.Neighbors[i] != nullptr) {
                    // Find the opposite neighbor direction and reset the pointer
                    int oppositeIndex = (i + 4) % 8;
                    if (chunkComponent.Neighbors[i]->Neighbors[oppositeIndex] == &chunkComponent) {
                        chunkComponent.Neighbors[i]->Neighbors[oppositeIndex] = nullptr;  // Clear neighbor's reference to this chunk
                    }
                    chunkComponent.Neighbors[i] = nullptr;  // Clear this chunk's neighbor reference
                }
            }

            // Destroy the chunk entity
            m_ActiveScene->DestroyEntity(it->second);

            // Erase the chunk from the loaded map safely
            m_LoadedChunks.erase(it);
            FSE_INFO("Chunk ({0}, {1}) successfully removed from ChunkManager.", chunkX, chunkY);
        }
        else
        {
            FSE_WARN("Trying to unload chunk that isn't loaded: ({0}, {1})", chunkX, chunkY);
        }
    }

    void ChunkManager::GenerateNewChunk(int chunkX, int chunkY) {
        Entity centerChunk = m_ActiveScene->CreateEntity("Chunk");
        auto& centerChunkComponent = centerChunk.AddComponent<ChunkComponent>();
        centerChunkComponent.ChunkCoords[0] = chunkX;
        centerChunkComponent.ChunkCoords[1] = chunkY;
        centerChunkComponent.IsAwake = true;
        centerChunk.AddComponent<NativeScriptComponent>().Bind<ChunkBehavior>();

        // Generate the 3x3 chunk grid
        GenerateNoiseFor3x3Chunks(chunkX, chunkY, centerChunkComponent);

        // Add only the center chunk to the loaded chunks map
        m_LoadedChunks[{chunkX, chunkY}] = centerChunk;

        // Populate neighbors for the new chunk
        PopulateNeighborsForChunk(centerChunk, chunkX, chunkY);
    }

    void ChunkManager::GenerateNoiseFor3x3Chunks(int centerChunkX, int centerChunkY, ChunkComponent& centerChunkComponent) {
        int startX = centerChunkX - 1;
        int startY = centerChunkY - 1;

        // Temporary storage for the 3x3 grid of chunks
        ChunkComponent chunks[3][3];

        // Seed and generate each chunk in the 3x3 grid
        for (int dx = 0; dx < 3; ++dx) {
            for (int dy = 0; dy < 3; ++dy) {
                int chunkX = startX + dx;
                int chunkY = startY + dy;

                // Set the seed based on the chunk coordinates
                int seed = SettingsManager::GetSetting<int>("WorldSeed");
                int modifiedSeed = seed ^ (chunkX * 374761393 + chunkY * 668265263);
                srand(modifiedSeed);

                // Populate this chunk's noise grid
                for (int x = 0; x < 64; ++x) {
                    for (int y = 0; y < 64; ++y) {
                        float randomValue = static_cast<float>(rand()) / RAND_MAX;
                        if (randomValue > 0.5f) {
                            ElementInterface::SetElementType(chunks[dx][dy].Cells[x][y], ElementType::Dirt);
                        }
                        else {
                            ElementInterface::SetElementType(chunks[dx][dy].Cells[x][y], ElementType::Air);
                        }
                    }
                }
            }
        }

        // Smooth the terrain for the 3x3 grid
        for (int dx = 0; dx < 3; ++dx) {
            for (int dy = 0; dy < 3; ++dy) {
                SmoothTerrain(chunks[dx][dy]);
            }
        }

        // Copy the center chunk to the centerChunkComponent
        centerChunkComponent = chunks[1][1];
    }
    //Helper Functions

    void ChunkManager::PopulateNeighborsForChunk(Entity& chunk, int chunkX, int chunkY) {
        auto& chunkComponent = chunk.GetComponent<ChunkComponent>();

        static const std::vector<std::pair<int, int>> neighborOffsets = {
            { 0,  1},  // North
            { 1,  1},  // North-East
            { 1,  0},  // East
            { 1, -1},  // South-East
            { 0, -1},  // South
            {-1, -1},  // South-West
            {-1,  0},  // West
            {-1,  1},  // North-West
        };

        for (int i = 0; i < 8; ++i) {
            int neighborX = chunkX + neighborOffsets[i].first;
            int neighborY = chunkY + neighborOffsets[i].second;

            auto it = m_LoadedChunks.find({ neighborX, neighborY });
            if (it != m_LoadedChunks.end()) {
                // Set this chunk's neighbor
                chunkComponent.Neighbors[i] = &it->second.GetComponent<ChunkComponent>();

                // Set the neighbor's corresponding slot to this chunk
                int oppositeIndex = (i + 4) % 8; // Calculate the opposite direction
                it->second.GetComponent<ChunkComponent>().Neighbors[oppositeIndex] = &chunkComponent;
            }
        }
    }

    std::pair<Entity, std::pair<int, int>> ChunkManager::GetChunkAtWorldCoords(int cellX, int cellY) {
        // Convert world coordinates to chunk coordinates
        int64_t chunkCoordsX = (cellX >= 0) ? (cellX / 64) : ((cellX + 1) / 64) - 1;
        int64_t chunkCoordsY = (cellY >= 0) ? (cellY / 64) : ((cellY + 1) / 64) - 1;

        std::pair<int, int> chunkCoords = { chunkCoordsX, chunkCoordsY };

        // Check if the chunk exists in the loaded chunks
        auto it = m_LoadedChunks.find(chunkCoords);
        if (it != m_LoadedChunks.end()) {
            // Return the chunk and its coordinates
            return { it->second, chunkCoords };
        }

        // If no chunk is found, return a default entity (can be handled gracefully by the caller)
        return { Entity(), {-1, -1}};
    }
  
}
