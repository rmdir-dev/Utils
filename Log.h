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

    template<typename T>
    inline const char* toString(const T& t)
    {
        return " !NO TYPE FOUND! ";
    }

    template<>
    inline const char* toString<const char*>(const char* const& c)
    {
        return c;
    }

    template<>
    inline const char* toString<std::string>(const std::string& s)
    {
        return s.c_str();
    }

    template<>
    inline const char* toString<Event::Event>(const Event::Event& e)
    {
        return e.toString().c_str();
    }

    template<>
    const char* toString<int>(const int& i)
    {
        return std::to_string(i).c_str();
    }

    template<typename First>
    void getMessage(char* buffer, int& index, First&& first)
    {
        const char* formatted = toString<First>(first);
        int length = strlen(formatted);
        memcpy(&buffer[index], formatted, length);
        index += length;
    }

    template<typename First, typename... Args>
    void getMessage(char* buffer, int& index, First&& first, Args&&... args) 
    {
        std::cout << first << "\n";
        const char* formatted = toString<First>(first);
        int length = strlen(formatted);
        memcpy(&buffer[index], formatted, length);
        index += length;
        if(sizeof...(Args))
        {
            getMessage(buffer, index, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    void fillBuffer(LogLevel level, Args... args)
    {
        char buffer[1024 * 10];
        int index = 0;
        
        //perfect forwarding args to fill the buffer args per args.
        getMessage(buffer, index, std::forward<Args>(args)...);

        //Null character to end the string.
        buffer[index] = 0;

        std::cout << buffer << "\n";
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

