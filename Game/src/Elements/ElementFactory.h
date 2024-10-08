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

	// updated 9 / 6 to use scopes instead of raw pointers for memory saftey
	// updated 9 / 6 later in the day to use refs so that other parts of the code dont need to manage the pointer when using
	// updated again to raw pointers as the element cache was having problems being filled with null pointers
	// could use a <T> or lamda or something to automate this
    class ElementFactory
    {
    public:
        static Scope<ElementInterface> CreateElementInstance(ElementType type)
        {
            switch (type)
            {
            case ElementType::Invalid:
                FSE_ERROR("Invalid Element!");
                return nullptr;
            case ElementType::Air:
                return CreateScope<AirElement>();
            case ElementType::Dirt:
                return CreateScope<DirtElement>();
            case ElementType::Sand:
                return CreateScope<SandElement>();
            case ElementType::Water:
                return CreateScope<WaterElement>();
            case ElementType::Stone:
                return CreateScope<StoneElement>();
            default:
                FSE_ERROR("Unknown ElementType: {0}", static_cast<int>(type));
                return nullptr;
            }
        }
    };
}
