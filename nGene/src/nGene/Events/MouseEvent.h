#pragma once

#include "Event.h"

namespace nGene {
	
	class NGN_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y):
			m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMove)
		EVENT_CLASS_CATEGORY(ECatMouse | ECatInput)

	private:
		float m_MouseX, m_MouseY;
	};

	class NGN_API MouseButtonEvent : public Event
	{
	public: 
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(ECatMouse | ECatMouseButton | ECatInput)

	protected:
		MouseButtonEvent(int button) :
			m_Button(button) {}

		int m_Button;
	};

	class NGN_API MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(int button):
			MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPress)
	};

	class NGN_API MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(int button):
			MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleaseEvent: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonRelease)
	};
}