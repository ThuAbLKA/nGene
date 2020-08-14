#pragma once

#include "../Core.h"
#include "../../ngpch.h";

namespace nGene {

	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,
		WindowMinimize,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPress,
		KeyRelease,
		MouseButtonPress,
		MouseButtonRelease,
		MouseMove,
		MouseScroll,
	};

	// for filtering the events
	enum EventCategory
	{
		None = 0,
		ECatApplication = BIT(0),
		ECatInput = BIT(1),
		ECatKeyboard = BIT(2),
		ECatMouse = BIT(3),
		ECatMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
					     virtual EventType GetEventType() const override { return GetStaticType(); }\
						 virtual const char* GetName() const override { return type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetEventCategoryFlags() const override { return category; }

	class NGN_API Event
	{
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetEventCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetEventCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : m_Event(event)
		{

		}

		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStatticType())
			{
				m_Event.m_Handled - func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

}