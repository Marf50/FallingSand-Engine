#include "fsepch.h"
#include "FallingSandEngine/Core/Input.h"
#include "FallingSandEngine/Core/Application.h"
#include <GLFW/glfw3.h>

// Refactored 8/7/24 with Input.h

namespace FallingSandEngine
{
	bool Input::IsKeyPressed(KeyCode keycode)
	{
		//grabs application that grabs window that grabs glfw(windows window)
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, (int)keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	
	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float,float> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::pair<float, float>(xpos, ypos);
	}
	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();

		return x;
	}
	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		

		return y;
	}
	
}