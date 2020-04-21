#pragma once

#include "Event.h"

struct WindowSize
{
    union
    {
        float width;
        float x;
    };

    union
    {
        float height;
        float y;
    };    
};

namespace Event 
{
    class ApplicationEvent : public Event
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        EVENT_CLASS_CATEGORY(CatApplication);

    protected:
        ApplicationEvent()
        {}

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    protected:
    };

    class WindowResize : public ApplicationEvent 
    {
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        FUNCTIONS
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    public:
        WindowResize(float width, float height)
            : m_WindowSize({width, height})
        {}

        inline WindowSize GetWindowSize() const 
        {
            return m_WindowSize;
        }

        std::string toString() const override
        {
            std::stringstream ss;
    		ss << "Window resize : " << m_WindowSize.x << "width " << m_WindowSize.y << "height";
    		return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize);

        //!!!!!!!!!!!!!!!!!!!!!!!!!!
        //        VARIABLES
        //!!!!!!!!!!!!!!!!!!!!!!!!!!
    private:
        WindowSize m_WindowSize;
    };
}