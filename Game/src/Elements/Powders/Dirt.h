#pragma once
#include "Powder.h"

namespace FallingSandEngine
{
	class DirtElement : public Powder
	{
	public:
		virtual void OnUpdate(int x, int y, ChunkComponent& chunk) override
		{
			Move(x, y, chunk);
		}
		virtual glm::vec4 GetColor() const override
		{
			return { 0.56f,0.42f,0.27f,1.0f };
		}
		uint8_t GetDensity() const override { return 50; }
		uint8_t GetStackingFactor() const override{ return 1; }

	};
}