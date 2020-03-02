#pragma once

#include "pch.h"
#include "String.h"
#include <glm/glm.hpp>

#define LEVEL_INFO      0
#define LEVEL_WARNING   1
#define LEVEL_ERROR     2
#define LEVEL_FATAL     3

namespace Log
{
    enum class LogLevel 
    {
        Info = 0,
        Warning,
        Error,
        Fatal
    };

    template<typename T>
    const char* toString(const T& t)
    {
        return " !NO TYPE FOUND! ";
    }

    template<>
    const char* toString<int>(const int& i)
    {
        return std::to_string(i).c_str();
    }

    template<typename First>
    void logOutput(char* buffer, int& index, First&& first)
    {
        const *char formatted = toString<First>(first);
        int length = strlen(formatted);
        memcpy(&buffer[index], formatted, length);
        index += length;
    }

    template<typename First, typename... Args>
    void getMessage(char* buffer, int& index, First&& first, Args&&... args) 
    {
        const *char formatted = toString<First>(first);
        int length = strlen(formatted);
        memcpy(&buffer[index], formatted, length);
        index += length;
        if(sizeof...(Args))
        {
            logOutput(buffer, int& index, std::forward<Args>(args)...);
        }
    }

    template<typename... Args>
    void fillBuffer(LogLevel level, Args... args)
    {
        char buffer[1024 * 10];
        int index = 0;
        
        //perfect forwarding args to fill the buffer args per args.
        logOutput(buffer, index, std::forward<Args>(args)...);

        //Null character to end the string.
        buffer[index] = 0;
    }
}