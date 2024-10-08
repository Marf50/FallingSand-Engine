#pragma once
#include "Elements/Element.h"
//#include "Elements/ElementFactory.h"


namespace FallingSandEngine
{
	class Liquid : public Element
	{
	public:
        virtual float GetStability(int x, int y, ChunkComponent& chunk) override { return 0; }
		virtual void OnUpdate(int x, int y, ChunkComponent& chunk) = 0;
		//virtual uint8_t GetDensity() override;
	protected:

        virtual void Move(int x, int y, ChunkComponent& chunk)
        {
            
            SetFlag(chunk.Cells[x][y], UPDATED_FLAG, true);

            AddVelocityY(chunk.Cells[x][y], Gravity);

            int8_t velocityY = GetVelocityY(chunk.Cells[x][y]);
            int8_t velocityX = GetVelocityX(chunk.Cells[x][y]);

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
                    if (MoveCell(x, y, newX, newY, chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
                        AwakeAround(newX, newY, chunk);
                        AwakeAround(x, y, chunk);
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
                    if (MoveCell(x,y,newX,newY,chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
                        AwakeAround(newX, newY, chunk);
                        AwakeAround(x, y, chunk);
                        return;
                    }
                }
            }

            // Check diagonal movement to the left or right
            if (AttemptHorizontalMove(x, y, chunk))
            {
                SetVelocityY(chunk.Cells[x][y], 0);
                return; // Diagonal movement successful, no need to reset velocity
            }

            // If no movement occurred, reset velocity

            SetVelocityY(chunk.Cells[x][y], 0);
            SetVelocityX(chunk.Cells[x][y], 0);
            SetFlag(chunk.Cells[x][y], AWAKE_FLAG, false);
        }

		bool AttemptHorizontalMove(int x, int y, ChunkComponent& chunk)
        {
            


			if (chunk.RandomNumber)
			{
				if (CanMoveTo(x - 1, y, chunk))
				{
                    AddVelocityX(chunk.Cells[x][y], -2);
                    if (MoveCell(x,y,x-1,y,chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);
                        AwakeAround(x - 1, y, chunk);
                        AwakeAround(x , y, chunk);
                        chunk.RandomNumber = !chunk.RandomNumber;
                        return true;
                    }
				}
				else if (CanMoveTo(x + 1, y, chunk))
				{
                    AddVelocityX(chunk.Cells[x][y], 2);
                    if (MoveCell(x,y,x+1,y,chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);                       
                        AwakeAround(x + 1, y, chunk);
                        AwakeAround(x , y, chunk);
                        chunk.RandomNumber = !chunk.RandomNumber;
                        return true;
                    }
				}
			}
			else
			{

                if (CanMoveTo(x + 1, y, chunk))
                {
                    AddVelocityX(chunk.Cells[x][y], 2);
                    if (MoveCell(x, y, x + 1, y, chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);                     
                        AwakeAround(x + 1, y, chunk);
                        AwakeAround(x , y, chunk);
                        chunk.RandomNumber = !chunk.RandomNumber;
                        return true;
                    }
                }
				else if (CanMoveTo(x - 1, y, chunk))
                {
                    AddVelocityX(chunk.Cells[x][y], -2);
                    if (MoveCell(x, y, x - 1, y, chunk))
                    {
                        SetFlag(chunk.Cells[x][y], AWAKE_FLAG, true);                       
                        AwakeAround(x - 1, y, chunk);
                        AwakeAround(x , y, chunk);
                        chunk.RandomNumber = !chunk.RandomNumber;
                        return true;
                    }
                }
			}
            return false;
		}
	};
}