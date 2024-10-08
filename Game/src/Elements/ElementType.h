#pragma once
#include <cstdint>
namespace FallingSandEngine
{
	// add by name
	enum class ElementType : uint16_t
	{
		Invalid = 0,
		Solid,
		Empty,
		Air,
		Dirt,
		Sand,
		Water,
		Stone,
		

		Count = 65535
		
	};


}