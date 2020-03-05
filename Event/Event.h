#pragma once
#include "../pch.h"

#define BIND_EVENT_FCT(x) std::bind(&x, this, std::placeholders::_1)

namespace Event
{
    //All event type possible
    enum class EventType 
    {
        NONE = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseBUttonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    //Event category flags.
    enum EventCategory
    {
        NONE = 0,
        CatApplication  = BITFIELD(0),
        CatInput        = BITFIELD(1),
        CatKeyboard     = BITFIELD(2),
        CatMouse        = BITFIELD(3),
        CatMouseButton  = BITFIELD(4)
    };

    /*This define able us to initialize the type with only one line.*/
#define EVENT_CLASS_TYPE(type)	static EventType getStaticType() { return EventType::type; }\
                                virtual EventType getType() const override { return getStaticType(); }\
                                virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

    class Event
    {
    public:
        virtual EventType getType() const = 0;
        virtual const char* getName() const = 0;
        virtual int getCategoryFlags() const = 0;
        virtual std::string toString() const { getName(); }

        inline bool isInCategory(EventCategory cat) const 
        {
            return getCategoryFlags() & cat;
        }

    public:
        bool m_Handled;
    };

    class Dispatcher
   	{
       	template<typename T>
       	using EventFn = std::function<bool(T&)>;

   	public:
       	Dispatcher(Event& event)
   			: m_Event(event)
   			{}

       	template<typename T>
       	bool dispatch(EventFn<T> func)
       	{
       		if(m_Event.getType() == T::getStaticType())
       		{
       			m_Event.m_Handled = func(*(T*)&m_Event);
       			return true;
       		}
       		return false;
       	}

   	private:
       	Event& m_Event;
   	};
}
