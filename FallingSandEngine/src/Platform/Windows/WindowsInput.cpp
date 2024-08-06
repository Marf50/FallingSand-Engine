#include "fsepch.h"
#include "WindowsInput.h"
#include "FallingSandEngine/Core/Application.h"
#include <GLFW/glfw3.h>

namespace FallingSandEngine
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		//grabs application that grabs window that grabs glfw(windows window)
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	
	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	std::pair<float,float> WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return std::pair<float, float>(xpos, ypos);
	}
	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();

		return x;
	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		

		return y;
	}
	
}