#pragma once
#include "Powder.h"

namespace FallingSandEngine
{
	class SandElement : public Powder
	{
	public:
		virtual void OnUpdate(int x, int y, ChunkComponent& chunk) override
		{
			Move(x,y,chunk);
		}
		virtual glm::vec4 GetColor() const override
		{
			return { 0.9f,0.9f,0.6f,1.0f };
		}
		uint8_t GetDensity() const override { return 50; }
		uint8_t GetStackingFactor() const override { return 5; }
	};
}