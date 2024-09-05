#pragma once
#include "Elements/ElementFactory.h"

namespace FallingSandEngine
{
	class Solid : public Element 
	{
	public:
		virtual void OnUpdate(int x, int y, ChunkComponent& chunk) = 0;
		virtual void Move(int x, int y, ChunkComponent& chunk)
		{
			SetFlag(chunk.Cells[x][y], AWAKE_FLAG, false);
		}
	};
}