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
            ElementType targetType = GetElementType(chunk.Cells[x][y]);
            

            auto it = chunk.ElementCache.find(targetType);
            if (it != chunk.ElementCache.end())
            {
                Scope<ElementInterface>& targetElement = it->second;

                if (targetElement)
                {
                    float targetStablility = targetElement->GetStability(x, y, chunk);

                    float random = ((float)rand() / RAND_MAX);
                    //FSE_INFO("{0} {1}", targetStablility, random);
                    if (random >= targetStablility)
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
                }
            }
        }

        virtual void AwakeAround(int x, int y, ChunkComponent& chunk)
        {
            // Offsets for all 8 neighboring cells
            const int offsets[8][2] = {
                {-1, -1}, {0, -1}, {1, -1},
                {-1,  0},          {1,  0},
                {-1,  1}, {0,  1}, {1,  1}
            };

            for (int i = 0; i < 8; ++i)
            {
                int neighborX = x + offsets[i][0];
                int neighborY = y + offsets[i][1];
                Awake(neighborX, neighborY, chunk);
            }
        }
        virtual void Awake(int x, int y, ChunkComponent& chunk)
        {
            ChunkComponent* targetChunk = nullptr;
            targetChunk = &chunk;
            int targetX = x;
            int targetY = y;

            // Check if the target cell is within the current chunk's bounds
            if (!IsInSameChunk(0, 0, x, y))
            {
                // Determine the neighbor direction
                int neighborDirection = GetNeighborDirection(0, 0, x, y);
                if (neighborDirection == -1)
                {
                    return; // Invalid direction, do nothing
                }

                targetChunk = chunk.Neighbors[neighborDirection];
                if (targetChunk == nullptr)
                {
                    return; // Neighbor chunk doesn't exist, do nothing
                }

                // Adjust target coordinates for the neighboring chunk
                targetX = (x + 64) % 64;
                targetY = (y + 64) % 64;
            }
            // Ensure the adjusted indices are within bounds
            if (targetX >= 0 && targetX < 64 && targetY >= 0 && targetY < 64)
            {
                ElementType targetType = GetElementType(targetChunk->Cells[targetX][targetY]);

                //FSE_INFO("Looking for cellType {0} in ElementCache. Cache currently has {1} entries.", static_cast<int>(targetType), chunk.ElementCache.size());
                auto it = targetChunk->ElementCache.find(targetType);
                if (it != targetChunk->ElementCache.end())
                {
                    Scope<ElementInterface>& targetElement = it->second;

                    if (targetElement)
                    {
                        targetElement->TryAwake(targetX, targetY, *targetChunk);
                    }
                }
            }
        }
		static const int8_t Gravity = 1;


        //movement helpers 
        bool MoveCell(int startX, int startY, int endX, int endY, ChunkComponent& chunk)
        {
            if (IsInSameChunk(startX, startY, endX, endY))
            {
                std::swap(chunk.Cells[startX][startY], chunk.Cells[endX][endY]);
                return true;
            }
            else
            {
                return MoveToNeighboringChunk(startX, startY, endX, endY, chunk);
            }
        }
        bool MoveToNeighboringChunk(int startX, int startY, int endX, int endY, ChunkComponent& chunk)
        {
            // Determine the target chunk
            int neighborDirection = GetNeighborDirection(startX, startY, endX, endY);
            if (neighborDirection == -1)
                FSE_ERROR("Invalid Neighbor Direction! might cause memory corruption");

            ChunkComponent* neighborChunk = chunk.Neighbors[neighborDirection];

            if (neighborChunk == nullptr)
            {
                FSE_ERROR("Failed to move: Neighbor chunk in direction {0} is null", neighborDirection);
                return false;
            }

            // Adjust target coordinates for the neighboring chunk
            int neighborTargetX = (endX + 64) % 64;
            int neighborTargetY = (endY + 64) % 64;

            if (neighborTargetX >= 0 && neighborTargetX < 64 && neighborTargetY >= 0 && neighborTargetY < 64)
            {
                std::swap(chunk.Cells[startX][startY], neighborChunk->Cells[neighborTargetX][neighborTargetY]);
                return true;
            }
            else
            {
                FSE_ERROR("Invalid neighbor chunk coordinates: ({0}, {1})", neighborTargetX, neighborTargetY);
            }

            return false;
        }
        virtual bool CanMoveTo(int x, int y, ChunkComponent& chunk)
        {
            // Check if the target cell is within the current chunk's bounds
            if (IsInSameChunk(0, 0, x, y))
            {
                // Proceed with the usual check within the same chunk
                ElementType targetType = GetElementType(chunk.Cells[x][y]);

                auto it = chunk.ElementCache.find(targetType);
                if (it != chunk.ElementCache.end())
                {
                    Scope<ElementInterface>& targetElement = it->second;

                    if (targetElement)
                    {
                        uint8_t currentDensity = GetDensity();
                        uint8_t targetDensity = targetElement->GetDensity();

                        return currentDensity > targetDensity;
                    }
                }

                return false;
            }
            else
            {
                // We're trying to move to a neighboring chunk
                int neighborDirection = GetNeighborDirection(0, 0, x, y);
                ChunkComponent* neighborChunk = chunk.Neighbors[neighborDirection];

                if (neighborChunk == nullptr)
                {
                    //FSE_ERROR("Cannot move to ({0}, {1}): Neighbor chunk in direction {2} is null", x, y, neighborDirection);
                    return false;
                }

                // Adjust target coordinates for the neighboring chunk
                int neighborTargetX = (x + 64) % 64;
                int neighborTargetY = (y + 64) % 64;

                if (IsInSameChunk(0, 0, neighborTargetX, neighborTargetY))
                {
                    // Perform the usual CanMoveTo check in the neighboring chunk
                    ElementType targetType = GetElementType(neighborChunk->Cells[neighborTargetX][neighborTargetY]);
                  

                    auto it = neighborChunk->ElementCache.find(targetType);
                    if (it != neighborChunk->ElementCache.end())
                    {
                        Scope<ElementInterface>& targetElement = it->second;

                        if (targetElement)
                        {
                            uint8_t currentDensity = GetDensity();
                            uint8_t targetDensity = targetElement->GetDensity();

                            return currentDensity > targetDensity;
                        }
                    }
                }

                return false;
            }
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


            ChunkComponent* currentChunk = &chunk;
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

                // If the new position is out of bounds, use neighbor chunk
                if (!IsInSameChunk(startX, startY, x, y))
                {
                    // Determine the neighbor direction and try to move into the neighboring chunk
                    int neighborDirection = GetNeighborDirection(startX, startY, x, y);
                    //FSE_INFO("Moving to neighbor direction: {0}, from ({1}, {2}) to ({3}, {4})",neighborDirection, startX, startY, x, y);
                    if (neighborDirection == -1)
                    {
                        //FSE_ERROR("Invalid move: Neighbor direction is invalid!");
                        return { lastValidX, lastValidY };
                    }
                    ChunkComponent* neighborChunk = chunk.Neighbors[neighborDirection];

                    if (neighborChunk == nullptr)
                    {
                        //FSE_ERROR("Failed to move: Neighbor chunk in direction {0} is null!", neighborDirection);
                        return { lastValidX, lastValidY };
                    }

                    // Adjust the coordinates for the neighboring chunk
                    int neighborX = (x + 64) % 64;
                    int neighborY = (y + 64) % 64;

                    // If the new position in the neighboring chunk is valid, continue
                    if (IsInSameChunk(0, 0, neighborX, neighborY))
                    {
                        // Check if we can move to this position in the neighboring chunk
                        if (!CanMoveTo(neighborX, neighborY, *neighborChunk))
                        {
                            return { lastValidX, lastValidY };
                        }
                        
                        // Update the last valid move and the current chunk
                        lastValidX = x ;
                        lastValidY = y ;
                        currentChunk = neighborChunk; // Switch to the neighboring chunk
                    }
                    else
                    {
                        // Invalid position, stop movement
                        return { lastValidX, lastValidY };
                    }
                }
                else
                {
                    // If we can't move to the current cell, stop moving
                    if (!CanMoveTo(x, y, chunk))
                    {
                        return { lastValidX, lastValidY };
                    }
                    // Update the last valid move
                    lastValidX = x;
                    lastValidY = y;
                }
                
                
            }
            return { endX, endY };

        }

        //other helpers
        bool IsInSameChunk(int startX, int startY, int endX, int endY)
        {
            return (endX >= 0 && endX <= 63 && endY >= 0 && endY <= 63);
        }
        int GetNeighborDirection(int startX, int startY, int endX, int endY)
        {
            // Determine which direction the movement is going
            // Moving South (negative Y)
            if (endY < 0)
            {
                if (endX >= 0 && endX < 64) return 4; // South
                if (endX >= 64) return 3;             // South-East
                if (endX < 0) return 5;               // South-West
            }

            // Moving North (positive Y)
            if (endY >= 64)
            {
                if (endX >= 0 && endX < 64) return 0; // North
                if (endX >= 64) return 1;             // North-East
                if (endX < 0) return 7;               // North-West
            }

            // Moving West (negative X)
            if (endX < 0)
            {
                if (endY >= 0 && endY < 64) return 6; // West
            }

            // Moving East (positive X)
            if (endX >= 64)
            {
                if (endY >= 0 && endY < 64) return 2; // East
            }

            // If no valid direction, return error
            FSE_ERROR("Invalid neighbor direction calculation: ({0}, {1}) to ({2}, {3})", startX, startY, endX, endY);
            return -1; // Invalid direction
        }

	};
}