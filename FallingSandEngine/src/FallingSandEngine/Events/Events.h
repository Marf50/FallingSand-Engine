#pragma once

#include "FallingSandEngine/Core/Core.h"

#include <string>
#include <functional>


namespace FallingSandEngine
{
	// Events are Blocking, Events will be delt with when made stops everything
	// Might add buffer in future, with bus?

	//uses a enum to assign a event type
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	//uses enum to change a bit to keep track of category can use multipule catagories
	//used to filter events for other files
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class FSE_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); } //used for debug
		
		//takes in a event and a category and returns bool can return greater than one if in multipul categorys
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
		inline bool Handled() const { return m_Handled; }
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
	//exist for log
	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}