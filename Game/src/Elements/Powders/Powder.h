#pragma once
#include "Elements/Element.h"

//#include "Elements/ElementFactory.h"

namespace FallingSandEngine
{
	class Powder : public Element
	{
	public:
		virtual void OnUpdate(int x, int y, ChunkComponent& chunk) = 0;
        

	protected:
        
        virtual void Move(int x, int y, ChunkComponent& chunk)
        {
            
            SetFlag(chunk.Cells[x][y], UPDATED_FLAG, true);

            AddVelocityY(chunk.Cells[x][y], Gravity);

            int8_t velocityY = GetVelocityY(chunk.Cells[x][y]);
            int8_t velocityX = GetVelocityX(chunk.Cells[x][y]);

            //FSE_INFO("Cell VelocityX = {0}, Cell VelocityY = {1}", velocityX, velocityY);
            // Calculate the target position
            int targetY = y - velocityY;
            int targetX = x + velocityX;

            if (velocityX != 0)
                AddVelocityX(chunk.Cells[x][y], (GetVelocityX(chunk.Cells[x][y]) > 0 ? -GetFriction() : GetFriction()));
            if (velocityY != 0)
            {
                // Move towards target using Bresenham's algorithm
                auto [newX, newY] = MoveTowardsTarget(x, y, targetX, targetY, chunk);
                if (newX != x || newY != y)
                {
                    // Use MoveCell to swap or move between chunks
                    if (MoveCell(x, y, newX, newY, chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
                        AwakeAround(x, y, chunk);
                        AwakeAround(newX, newY, chunk);
                        chunk.RandomNumber = !chunk.RandomNumber;
                        return;
                    }
                }
            }
            if (velocityX != 0)
            {
                auto [newX, newY] = MoveTowardsTarget(x, y, targetX, y, chunk);
                if (newX != x || newY != y)
                {
                    SetVelocityY(chunk.Cells[x][y], 0);
                    if (MoveCell(x, y, newX, newY, chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
                        AwakeAround(x, y, chunk);
                        AwakeAround(newX, newY, chunk);
                        return;
                    }
                }
            }
            
            // Check diagonal movement to the left or right
            if (AttemptDiagonalMove(x, y, chunk))
            {
                return; // Diagonal movement successful, no need to reset velocity
            }

            // If no movement occurred, reset velocity
            
            SetVelocityY(chunk.Cells[x][y], 0);
            SetVelocityX(chunk.Cells[x][y], 0);
            SetFlag(chunk.Cells[x][y], AWAKE_FLAG, false);
        }

        bool AttemptDiagonalMove(int x, int y, ChunkComponent& chunk)
        {
            // Adjust velocities based on the random number for diagonal movement
            AddVelocityX(chunk.Cells[x][y], (chunk.RandomNumber ? -1 : 1) * GetStackingFactor());
            AddVelocityY(chunk.Cells[x][y], -1);

            // First random diagonal direction (left or right)
            if (chunk.RandomNumber)
            {
                // Try to move diagonally left
                if (CanMoveTo(x - 1, y - 1, chunk))
                {
                    if (MoveCell(x, y, x - 1, y - 1, chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
                        AwakeAround(x - 1, y - 1, chunk);
                        chunk.RandomNumber = !chunk.RandomNumber;
                        return true;
                    }
                }
                // Try to move diagonally right
                else if (CanMoveTo(x + 1, y - 1, chunk))
                {
                    if (MoveCell(x, y, x + 1, y - 1, chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
                        AwakeAround(x + 1, y - 1, chunk);
                        chunk.RandomNumber = !chunk.RandomNumber;
                        return true;
                    }
                }
            }
            // Second diagonal direction (right or left)
            else
            {
                // Try to move diagonally right
                if (CanMoveTo(x + 1, y - 1, chunk))
                {
                    if (MoveCell(x, y, x + 1, y - 1, chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
                        AwakeAround(x + 1, y - 1, chunk);
                        chunk.RandomNumber = !chunk.RandomNumber;
                        return true;
                    }
                }
                // Try to move diagonally left
                else if (CanMoveTo(x - 1, y - 1, chunk))
                {
                    if (MoveCell(x, y, x - 1, y - 1, chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
                        AwakeAround(x - 1, y - 1, chunk);
                        chunk.RandomNumber = !chunk.RandomNumber;
                        return true;
                    }
                }
            }
            return false; // No diagonal move was possible
        }

	};
}