#pragma once
#include "Solid.h"
namespace FallingSandEngine
{
	class StoneElement : public Solid
	{
	public:
		virtual void OnUpdate(int x, int y, ChunkComponent& chunk) override
		{
			Move(x, y, chunk);
		}
		virtual glm::vec4 GetColor() const override
		{
			return { 0.8f,0.8f,0.8f,1.0f };
		}
		uint8_t GetDensity() const override { return 250; }
	};
}