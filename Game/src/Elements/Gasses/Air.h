#pragma once
#include "Gases.h"
namespace FallingSandEngine
{
	class AirElement : public Gas
	{
	public:
		virtual void OnUpdate(int x, int y, ChunkComponent& chunk) override
		{
			Move(x,y,chunk);
		}
		virtual glm::vec4 GetColor() const override
		{
			return { 1.0f,1.0f,1.0f,0.0f };
		}
		uint8_t GetDensity() const override { return 10; }

	};
}