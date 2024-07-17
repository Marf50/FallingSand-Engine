#pragma once
#include <fsepch.h>
#include "FallingSandEngine/Core.h"
#include "FallingSandEngine/Events/Events.h"

namespace FallingSandEngine
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		//makes a window using these props otherwise uses default

		WindowProps(const std::string& title = "Falling Sand Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{}
	};
	//general use, diffrent platform implimentation will be done on the Create() func
	class FSE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		//attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}