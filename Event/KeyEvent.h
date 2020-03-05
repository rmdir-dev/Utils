#pragma once

#include "Event.h"

namespace Event
{
    class KeyEvent : public Event
	{
	public:
    	inline int getKeyCode() const { return m_KeyCode; }

    	EVENT_CLASS_CATEGORY(CatKeyboard | CatInput);

	protected:
    	KeyEvent(int KeyCode)
			: m_KeyCode(KeyCode)
		{}

	protected:
    	int m_KeyCode;
	};

    class KeyPressed : public KeyEvent
    {
    public:
    	KeyPressed(int KeyCode, int repeatCount)
    		: KeyEvent(KeyCode), m_RepeatKeyCount(repeatCount)
    	{}

    	inline int getRepeatCount() const { return m_RepeatKeyCount; }

    	std::string toString() const override
    	{
    		std::stringstream ss;
    		ss << "Key pressed Event : " << m_KeyCode << " (" << m_RepeatKeyCount << " repeats)";
    		return ss.str();
    	}

    	EVENT_CLASS_TYPE(KeyPressed);

    private:
    	int m_RepeatKeyCount;
    };
}
