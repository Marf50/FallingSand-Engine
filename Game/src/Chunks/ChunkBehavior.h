#pragma once
#include "Elements/ElementFactory.h"
namespace FallingSandEngine
{
	class ChunkBehavior :  public ScriptableEntity
	{
	public:
		void OnCreate() override
		{
			
			auto chunk = GetComponent<ChunkComponent>();
			//FSE_INFO("chunk script created with adress {0}", (void*)&chunk);
			for (int x = 0; x < 64; ++x)
			{
				for (int y = 0; y < 64; ++y)
				{
					ElementInterface::SetElementType(chunk.Cells[x][y],(ElementType::Air));

					// set clean memory
					ElementInterface::SetFlag(chunk.Cells[x][y], ElementInterface::UPDATED_FLAG, false);
					ElementInterface::SetVelocityX(chunk.Cells[x][y], 0);
					ElementInterface::SetVelocityY(chunk.Cells[x][y], 0);
				}
			}
			//FSE_INFO("Chunk Created at coords {0} , {1}", chunk.ChunkCoords.x, chunk.ChunkCoords.y);
		}
		void OnUpdate(Timestep ts) override
		{
			FSE_PROFILE_FUNCTION();
			// awake check
			auto& chunk = GetComponent<ChunkComponent>();
			if (!chunk.IsAwake)
				return;
			
			// Tick logic
			m_accumulatedTime += ts;
			if (m_accumulatedTime < tickInterval)
				return;
			m_accumulatedTime = m_accumulatedTime - tickInterval;


			// clear cache to start new update
			//FSE_INFO("Updating Chunk {0}", (void*)&chunk);
			for (auto& entry : chunk.ElementCache)
			{
				delete entry.second;
			}
			chunk.ElementCache.clear();
			chunk.ElementCache[ElementType::Air] = ElementFactory::CreateElementInstance(ElementType::Air);
			//Dirty Rectangle
			int minX = 63, minY = 63, maxX = 0, maxY = 0;
			bool hasAwakeCells = false;
			for (int x = 0; x < 64; ++x)
			{
				for (int y = 0; y < 64; ++y)
				{
					
					FSE_PROFILE_SCOPE("For Loop 1")
					ElementInterface::SetFlag(chunk.Cells[x][y], 0, false);
					ElementType cellType = ElementInterface::GetElementType(chunk.Cells[x][y]);
					if (cellType == ElementType::Air)
						continue;
					if (chunk.ElementCache.find(cellType) == chunk.ElementCache.end())
					{
						FSE_PROFILE_SCOPE("Cacheing")
						chunk.ElementCache[cellType] = ElementFactory::CreateElementInstance(cellType);
						//FSE_INFO("Cached Element {0}", (uint16_t)cellType);
					}
					if (ElementInterface::GetFlag(chunk.Cells[x][y], ElementInterface::AWAKE_FLAG) == true)
					{
						FSE_PROFILE_SCOPE("Dirty Rect Gen")
						if (x < minX) minX = x;
						if (x > maxX) maxX = x;
						if (y < minY) minY = y;
						if (y > maxY) maxY = y;
						hasAwakeCells = true;
					}
				}
			}

			if (!hasAwakeCells)
				return;
			//FSE_INFO("Cache size after population: {0}", chunk.ElementCache.size());
			for (int x = minX; x <= maxX; ++x)
			{
				for (int y = minY; y <= maxY; ++y)
				{
					
					if (ElementInterface::GetFlag(chunk.Cells[x][y], ElementInterface::AWAKE_FLAG) == false)
						continue;
					if (ElementInterface::GetFlag(chunk.Cells[x][y], ElementInterface::UPDATED_FLAG) == true)
						continue;
					ElementType cellType = ElementInterface::GetElementType(chunk.Cells[x][y]);
					ElementInterface* element = chunk.ElementCache[cellType];
					if (element != nullptr) 
					{
						FSE_PROFILE_SCOPE("Updating Rectangle")
						element->OnUpdate(x, y, chunk);
						chunk.RandomNumber = !chunk.RandomNumber;
						//FSE_INFO("Updating cell {0},{1}", x, y);
					}
				}
			}
			


		}
		void OnDestroy() override
		{

		}
	private:
		float m_accumulatedTime = 0.0f;
		const float tickInterval = 0.008f; // Tick interval 30 ticks a second
	};
}