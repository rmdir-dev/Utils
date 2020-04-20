#pragma once

#include "pch.h"
#include <glm/glm.hpp>
#include "Event/Event.h"

#define LEVEL_INFO      0
#define LEVEL_WARNING   1
#define LEVEL_ERROR     2
#define LEVEL_CRITICAL  3

namespace Log
{
    enum class LogLevel 
    {
        Info = 0,
        Warning,
        Error,
        Critical
    };

    /*
    Send Log message to the right platform (OS)
    Args:
     - level : the message Log level
     - message : the message buffer.
    */
    void platformLogMessage(LogLevel level, const char* message);
    
    /*
    Platform break, set a break point in function of the OS.
    */
    void platformBreak();

    /*
        Convert a variable T into string,
        Use toString<TYPE>()
        This will be used if no the type was not found.
        If this function is used, create a toString<TYPE>() function for that type.
    */
    template<typename T>
    inline const char* toString(const T& t)
    {
        return " !NO TYPE FOUND! ";
    }

    /*
    "Convert" const char* to const char*
    */
    template<>
    inline const char* toString<const char*>(const char* const& c)
    {
        return c;
    }

    /*
    Convert std::string to const char*
    */
    template<>
    inline const char* toString<std::string>(const std::string& s)
    {
        return s.c_str();
    }

    /*
    Convert Event::Event to const char*
    */
    template<>
    inline const char* toString<Event::Event>(const Event::Event& e)
    {
        return e.toString().c_str();
    }

    /*
    Convert int to const char*
    */
    template<>
    inline const char* toString<int>(const int& i)
    {
        return std::to_string(i).c_str();
    }

    /*
    Convert unsigned int to const char*
    */
    template<>
    inline const char* toString<uint>(const uint& i)
    {
        return std::to_string(i).c_str();
    }

    /*
    Convert float to const char*
    */
    template<>
    inline const char* toString<float>(const float& f)
    {
        return std::to_string(f).c_str();
    }

    /*
    Get the log message.
    */
    template<typename First>
    void getMessage(char* buffer, int& index, First&& first)
    {
        //Convert First into const char*
        const char* formatted = toString<First>(first);
        //Get the lenght of the string
        int length = strlen(formatted);
        //Copy the message into the buffer.
        memcpy(&buffer[index], formatted, length);
        //Set the buffer index to the end of the message.
        index += length;
    }

    template<typename First, typename... Args>
    void getMessage(char* buffer, int& index, First&& first, Args&&... args) 
    {
        //Convert First into const char*
        const char* formatted = toString<First>(first);
        //Get the lenght of the string
        int length = strlen(formatted);
        //Copy the message into the buffer.
        memcpy(&buffer[index], formatted, length);
        //Set the buffer index to the end of the message.
        index += length;
        
        //If there is more args
        if(sizeof...(Args))
        {
            //Get the message of the other args.
            getMessage(buffer, index, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    void fillBuffer(LogLevel level, Args... args)
    {
        //Set the buffer
        char buffer[1024 * 10];
        //Set buffer index
        int index = 0;
        
        //perfect forwarding args to fill the buffer args per args.
        getMessage(buffer, index, std::forward<Args>(args)...);

        //Null character to end the string.
        buffer[index] = 0;
        
        //Return the log message.
        platformLogMessage(level, buffer);
    }
}

#ifndef CORE_LOG_LEVEL
#define CORE_LOG_LEVEL 0
#endif

#if CORE_LOG_LEVEL <= LEVEL_CRITICAL
#define CORE_CRITICAL(...) Log::fillBuffer(Log::LogLevel::Critical, __VA_ARGS__)
#else
#define CORE_CRITICAL(...)
#endif

#if CORE_LOG_LEVEL <= LEVEL_ERROR
#define CORE_ERROR(...) Log::fillBuffer(Log::LogLevel::Error, __VA_ARGS__)
#else
#define CORE_ERROR(...)
#endif

#if CORE_LOG_LEVEL <= LEVEL_WARNING
#define CORE_WARNING(...) Log::fillBuffer(Log::LogLevel::Warning, __VA_ARGS__)
#else
#define CORE_WARNING(...)
#endif

#if CORE_LOG_LEVEL <= LEVEL_INFO
#define CORE_INFO(...) Log::fillBuffer(Log::LogLevel::Info, __VA_ARGS__)
#else
#define CORE_INFO(...)
#endif

