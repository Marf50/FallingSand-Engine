#pragma once
#include "FallingSandEngine/Core/Window.h"

#include <GLFW/glfw3.h>

#include "FallingSandEngine/Renderer/GraphicsContext.h"

namespace FallingSandEngine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		//Attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;
		//stored for glfw
		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};
		//for class
		WindowData m_Data;
	};
}