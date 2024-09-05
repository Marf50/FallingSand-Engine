#pragma once


#include <cstdint>
#include "Element.h"

#include "Elements/Gasses/Air.h"

#include "Elements/Liquids/Water.h"

#include "Elements/Powders/Dirt.h"
#include "Elements/Powders/Sand.h"

#include "Elements/Solids/Stone.h"
namespace FallingSandEngine
{


	// could use a <T> or lamda or something to automate this
	class ElementFactory
	{
	public:
		static Element* CreateElementInstance(ElementType type)
		{
			switch (type)
			{
			case ElementType::Air:
				return new AirElement();
			case ElementType::Dirt:
				return new DirtElement();
			case ElementType::Sand:
				return new SandElement();
			case ElementType::Water:
				return new WaterElement();
			case ElementType::Stone:
				return new StoneElement();
			default:
				return nullptr;
			}
		}
	};
}
