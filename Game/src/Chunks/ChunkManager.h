#pragma once
#include "FallingSandEngine.h"

struct PairHash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const noexcept {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); // Combine the two hash values
    }
};

namespace FallingSandEngine {

    class ChunkManager {
    public:
        ChunkManager(Ref<Scene> activeScene, Entity playerEntity, int chunkLoadRadius = 2);
        void Setup(Ref<Scene> activeScene, Entity playerEntity, int chunkLoadRadius = 2);
        ~ChunkManager();
        

        std::unordered_map<std::pair<int, int>, Entity, PairHash>& GetChunks();
        void UpdateChunks(); // Call this every frame to manage chunk loading/unloading
        void SetChunkLoadRadius(int radius) { m_ChunkLoadRadius = radius; }

        void GenerateNewChunk(int chunkX, int chunkY);
        void GenerateNoiseFor3x3Chunks(int centerChunkX, int centerChunkY, ChunkComponent& centerChunkComponent);
        std::pair<Entity, std::pair<int, int>> GetChunkAtWorldCoords(int cellX, int cellY);

    private:
        Ref<Scene> m_ActiveScene;
        Entity m_PlayerEntity;
        int m_ChunkLoadRadius;

        std::unordered_map<std::pair<int, int>, Entity, PairHash> m_LoadedChunks; // Store active chunks

        std::pair<int, int> GetPlayerChunkCoords(); // Helper to get player's current chunk coordinates
        void LoadChunk(int chunkX, int chunkY); // Load a chunk
        void UnloadChunk(int chunkX, int chunkY); // Unload a chunk

        void PopulateNeighborsForChunk(Entity& chunk, int chunkX, int chunkY);
        void UpdateChunk(Entity chunkEntity); // Update a chunk
    };

}