#pragma once
#include "Elements/ElementFactory.h"
namespace FallingSandEngine
{
	class ChunkBehavior :  public ScriptableEntity
	{
	public:
		void OnCreate() override
		{
			//
			auto& chunk = GetComponent<ChunkComponent>();
			////FSE_INFO("chunk script created with adress {0}", (void*)&chunk);
			for (int x = 0; x < 64; ++x)
			{
				for (int y = 0; y < 64; ++y)
				{
					//ElementInterface::SetElementType(chunk.Cells[x][y], ElementType::Air);
					//ElementType cellType = ElementInterface::GetElementType(chunk.Cells[x][y]);
					//FSE_INFO("Set cell ({0}, {1}) to Air. Current cell type: {2}", x, y, static_cast<int>(cellType));
					// set clean memory
					ElementInterface::SetFlag(chunk.Cells[x][y], ElementInterface::UPDATED_FLAG, false);
					ElementInterface::SetFlag(chunk.Cells[x][y], ElementInterface::AWAKE_FLAG, false);
					ElementInterface::SetVelocityX(chunk.Cells[x][y], 0);
					ElementInterface::SetVelocityY(chunk.Cells[x][y], 0);
				}
			}
			FSE_INFO("Chunk Created at coords {0} , {1}", chunk.ChunkCoords[0], chunk.ChunkCoords[1]);
		}




		void OnUpdate(Timestep ts) override
		{
			
			// awake check
			auto& chunk = GetComponent<ChunkComponent>();
			if (!chunk.IsAwake)
				return;
			
			// Tick logic
			m_accumulatedTime += ts;
			if (m_accumulatedTime < tickInterval)
				return;
			m_accumulatedTime = m_accumulatedTime - tickInterval;

			

			//chunk.ElementCache.clear();
			
	
			//chunk.ElementCache[ElementType::Air] = ElementFactory::CreateElementInstance(ElementType::Air);
			//Dirty Rectangle
			int minX = 63, minY = 63, maxX = 0, maxY = 0;
			bool hasAwakeCells = false;


			for (int x = 0; x < 64; ++x)
			{
				for (int y = 0; y < 64; ++y)
				{
					ElementInterface::SetFlag(chunk.Cells[x][y], ElementInterface::UPDATED_FLAG, false);
					ElementType cellType = ElementInterface::GetElementType(chunk.Cells[x][y]);

					//if (cellType == ElementType::Air)
					//	continue;c

					if (chunk.ElementCache.find(cellType) == chunk.ElementCache.end())
					{
						chunk.ElementCache[cellType] = std::move(ElementFactory::CreateElementInstance(cellType));
						//PropagateCacheToNeighbors(cellType, chunk);
					}

					if (ElementInterface::GetFlag(chunk.Cells[x][y], ElementInterface::AWAKE_FLAG) == true)
					{
						
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





			for (int x = minX; x <= maxX; ++x)
			{
				for (int y = minY; y <= maxY; ++y)
				{
					
					if (ElementInterface::GetFlag(chunk.Cells[x][y], ElementInterface::AWAKE_FLAG) == false)
						continue;
					if (ElementInterface::GetFlag(chunk.Cells[x][y], ElementInterface::UPDATED_FLAG) == true)
						continue;
					ElementType cellType = ElementInterface::GetElementType(chunk.Cells[x][y]);
					Scope<ElementInterface>& element = chunk.ElementCache[cellType];
					if (element) 
					{
						FSE_PROFILE_SCOPE("Updating Rectangle")
						element->OnUpdate(x, y, chunk);
						chunk.RandomNumber = !chunk.RandomNumber;
					}
				}
			}
			


		}
		//helper for manageing caches
		//void PropagateCacheToNeighbors(ElementType cellType, ChunkComponent& chunk)
		//{
		//	for (int i = 0; i < 8; ++i) // Check all 8 neighbors
		//	{
		//		ChunkComponent* neighbor = chunk.Neighbors[i];
		//		if (neighbor != nullptr && neighbor->ElementCache.find(cellType) == neighbor->ElementCache.end())
		//		{
		//			neighbor->ElementCache[cellType] = ElementFactory::CreateElementInstance(cellType);
		//		}
		//	}
		//}

		void OnDestroy() override
		{

		}
	private:
		float m_accumulatedTime = 0.0f;
		const float tickInterval = 0.0008f; // Tick interval 30 ticks a second
	};
}