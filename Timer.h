#pragma once
#include <chrono>

using HrClock = std::chrono::high_resolution_clock;
using eTime = std::chrono::duration<double>;
using TPoint = std::chrono::high_resolution_clock::time_point;

class Timer {
private:
    TPoint start;

public:
    Timer();

    ~Timer();
};