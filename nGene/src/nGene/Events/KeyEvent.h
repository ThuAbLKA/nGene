#pragma once

#include "Event.h"

namespace nGene {
	
	class NGN_API KeyEvent : public Event
	{
	public: 
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(ECatKeyboard | ECatInput)

	protected:
		KeyEvent(int keycode): m_KeyCode(keycode) {}


		int m_KeyCode;
	};

	class NGN_API KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keycode, int repeatCount):
			KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeastCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		} 

		EVENT_CLASS_TYPE(KeyPress)
 
	private:
		int m_RepeatCount;
	};

	class NGN_API KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int keycode):
			KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyRelease)
	};
}