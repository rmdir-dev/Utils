#pragma once

#include "Event.h"


struct MousePosition
{
    float x;
    float y;
};

namespace Event
{
    class MouseEvent : public Event
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        EVENT_CLASS_CATEGORY(CatMouse | CatInput);

    protected:
        MouseEvent()
        {}

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    protected:
        
        
    };

    class MouseMoved : public MouseEvent
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        MouseMoved(float x, float y)
            : m_Position({x, y})
        {}

        inline MousePosition GetMousePosition() const { return m_Position; }

        std::string toString() const override
        {
            std::stringstream ss;
    		ss << "Mouse moved Event : " << m_Position.x << "x " << m_Position.y << "y";
    		return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    private:
        MousePosition m_Position;
        
    };

    class MouseButtonPressed : public MouseEvent
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        MouseButtonPressed(int buttonCode, int repeated)
            : m_ButtonCode(buttonCode), m_Repeated(repeated)
        {}

        inline int GetMouseButtonCode() const { return m_ButtonCode; }

        std::string toString() const override
        {
            std::stringstream ss;
    		ss << "Mouse button pressed Event : " << m_ButtonCode << " (" << m_Repeated << " repeats)";
    		return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    private:
        int m_ButtonCode;
        int m_Repeated;
    };
}