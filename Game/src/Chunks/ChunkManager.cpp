#include "ChunkManager.h"
#include "ChunkBehavior.h"



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
        // Unload all chunks on destruction
        for (auto& chunk : m_LoadedChunks) {

            UnloadChunk(chunk.first.first, chunk.first.second);
        }
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
        Entity chunk = m_ActiveScene->CreateEntity("Chunk");
        //FSE_INFO("Loading chunk with entity handle: {0} at coords ({1}, {2})", (uint32_t)(entt::entity)chunk, chunkX, chunkY);

        auto& chunkComponent = chunk.AddComponent<ChunkComponent>();
        chunkComponent.ChunkCoords[0] = chunkX;
        chunkComponent.ChunkCoords[1] = chunkY;
        chunkComponent.IsAwake = true;
        chunk.AddComponent<NativeScriptComponent>().Bind<ChunkBehavior>();

        m_LoadedChunks[{chunkX, chunkY}] = chunk;

        //FSE_INFO("Loaded chunk at ({0}, {1}), Entity memory address: {2}", chunkX, chunkY, (void*)&chunk);

        //Print out all loaded chunk entities to verify uniqueness
        //FSE_INFO("Current loaded chunks:");
        //for (const auto& pair : m_LoadedChunks) {
            //FSE_INFO("Chunk at ({0}, {1}) with entity handle: {2}, memory address: {3}",
                //pair.first.first, pair.first.second, (uint32_t)(entt::entity)pair.second, (void*)&pair.second);
        //}
    }

    void ChunkManager::UnloadChunk(int chunkX, int chunkY) {
        auto it = m_LoadedChunks.find({ chunkX, chunkY });
        if (it != m_LoadedChunks.end()) {
            m_ActiveScene->DestroyEntity(it->second);
            m_LoadedChunks.erase(it);
            //FSE_INFO("Unloaded chunk at ({0}, {1})", chunkX, chunkY);
        }
    }



    //Helper Functions

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
