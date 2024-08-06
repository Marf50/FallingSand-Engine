#include "fsepch.h"
#include "WindowsWindow.h"
#include "FallingSandEngine/Events/ApplicationEvents.h"
#include "FallingSandEngine/Events/KeyEvents.h"
#include "FallingSandEngine/Events/MouseEvents.h"
#include "Platform/OpenGl/OpenGLContext.h"



namespace FallingSandEngine
{
	// keeps track of glfw to not create multipule if several windows are opened
	static bool s_GLFWInitalized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		FSE_CORE_ERROR("GLFW Error ({0}) : {1}", error, description);
	}
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		FSE_PROFILE_FUNCTION();
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		FSE_PROFILE_FUNCTION();
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		FSE_PROFILE_FUNCTION();
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		

		FSE_CORE_INFO("Creating Window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		//inits glfw
		if (!s_GLFWInitalized)
		{
			//terminate on shutdown
			int success = glfwInit();
			FSE_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitalized = true;
		}
		//create window and makes pointer
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();
		
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
				
		});
		
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);

		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});
			
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event(keycode);
				data.EventCallback(event);

			});




		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrollEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
				
			});
			
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);

			});
	} 

	void WindowsWindow::Shutdown()
	{
		FSE_PROFILE_FUNCTION();
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		FSE_PROFILE_FUNCTION();
		glfwPollEvents();
		m_Context->SwapBuffers();
		
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		FSE_PROFILE_FUNCTION();
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
