#pragma once
#include "FallingSandEngine/Core/Core.h"
#include "KeyCodes.h"

// This class was refactored 8/7/24, removed like 20 lines of code and deleted windowsinput.h
// todo mouse codes


namespace FallingSandEngine
{
	
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}