#pragma once
#include <chrono>
#include <string>

using HrClock = std::chrono::high_resolution_clock;
using eTime = std::chrono::duration<double>;
using TPoint = std::chrono::high_resolution_clock::time_point;

/*
    Start the timer.
    THE TIMER MUST NOT BE A POINTER !
    Timer use it's life cycle to time your function, so it's better to allocate it on the stack,
    if you do allocate it on the heap DESTROY IT!
    
    Args:
    fctName = function name or the name of the part you want to debug.
    DEFAULT : "NO NAME"
    use __func__ to get the function name.
*/
class Timer {
private:
    TPoint start;
    std::string fctName;

public:
    /*
    Start the timer.
    THE TIMER MUST NOT BE A POINTER !
    Timer use it's life cycle to time your function, so it's better to allocate it on the stack,
    if you do allocate it on the heap DESTROY IT!

    Args:
    fctName = function name or the name of the part you want to debug.
    DEFAULT : "NO NAME"
    use __func__ to get the function name.
    */
    Timer(std::string fctName = "NO NAME");

    ~Timer();
};