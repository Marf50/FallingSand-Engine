#include "fsepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace FallingSandEngine
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		FSE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		FSE_PROFILE_FUNCTION();
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FSE_CORE_ASSERT(status, "Failed to initailize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		FSE_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}
