#pragma once
#include "FallingSandEngine/Scene/Components.h"
#include "FallingSandEngine/Scene/ElementInterface.h"
#include "ElementType.h"
namespace FallingSandEngine
{
	class Element : public ElementInterface
	{
	public:
		virtual ~Element() = default;

		virtual void OnUpdate(int x, int y, ChunkComponent& chunk) = 0;
		
		virtual uint8_t GetDensity() const = 0;
        virtual uint8_t GetFriction() const { return 1; }
        virtual uint8_t GetStackingFactor() const { return 0; }
        virtual void TryAwake(int x, int y, ChunkComponent& chunk)
        {
            SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
        }

        virtual void AwakeAround(int x, int y, ChunkComponent& chunk)
        {
            Awake(x - 1, y - 1, chunk);
            Awake(x    , y - 1, chunk);
            Awake(x + 1, y - 1, chunk);
            Awake(x - 1, y    , chunk);
            //Awake(x    , y    , chunk);
            Awake(x + 1, y    , chunk);
            Awake(x - 1, y + 1, chunk);
            Awake(x    , y + 1, chunk);
            Awake(x + 1, y + 1, chunk);
            
        }
        virtual void Awake(int x, int y, ChunkComponent& chunk)
        {
            if (x >= 0 && x < 63 && y >= 0 && y < 63)
            {
                ElementType targetType = GetElementType(chunk.Cells[x][y]);
                ElementInterface* targetElement = nullptr;

                auto it = chunk.ElementCache.find(targetType);
                if (it != chunk.ElementCache.end())
                {
                    targetElement = it->second;
                }
                targetElement->TryAwake(x, y, chunk);
            }
        }
		static const int8_t Gravity = 1;

		virtual bool CanMoveTo(int x, int y, ChunkComponent& chunk)
		{
			// could be better to not use a raw pointer
			ElementType targetType = GetElementType(chunk.Cells[x][y]);
			ElementInterface* targetElement = nullptr;

			auto it = chunk.ElementCache.find(targetType);
			if (it != chunk.ElementCache.end())
			{
				targetElement = it->second;
			}
			else
			{
				// chunk should have all elements
				//targetElement = ElementFactory::CreateElementInstance(targetType);
				//chunk.ElementCache[targetType] = targetElement;
			}
			//chunk will clear the cache at the end of the update
			if (targetElement)
			{
				uint8_t currentDensity = GetDensity();
				uint8_t targetDensity = targetElement->GetDensity();

				return currentDensity > targetDensity;
			}

			return false;

		}

        std::pair<int, int> MoveTowardsTarget(int startX, int startY, int endX, int endY, ChunkComponent& chunk)
        {
            int dx = abs(endX - startX);
            int dy = abs(endY - startY);
            int sx = (startX < endX) ? 1 : -1;
            int sy = (startY < endY) ? 1 : -1;
            int err = dx - dy;

            int x = startX;
            int y = startY;

           // FSE_INFO("Starting move from ({0}, {1}) to ({2}, {3})", startX, startY, endX, endY);

            int lastValidX = startX;
            int lastValidY = startY;

            int e2;
            while (x != endX || y != endY)
            {
                // Calculate next potential move
                e2 = 2 * err;

                if (e2 > -dy)
                {
                    err -= dy;
                    x += sx;
                }

                if (e2 < dx)
                {
                    err += dx;
                    y += sy;
                }

                // If the new position is out of bounds, break the loop
                if (x < 0 || x >= 64 || y < 0 || y >= 64)
                    break;

                // If we can't move to the current cell, stop moving
                if (!CanMoveTo(x, y, chunk))
                {
                    return { lastValidX, lastValidY };
                }
                // Update the last valid move
                lastValidX = x;
                lastValidY = y;
            }
            return { endX, endY };

        }

        
	};
}