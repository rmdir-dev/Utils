#include "Timer.h"
#include <iostream>

Timer::Timer(){
    start = HrClock::now();
}

Timer::~Timer(){
    TPoint end = HrClock::now();
    eTime elaspeTime = end - start;
    float ms = elaspeTime.count() * 1000;
    std::cout << ms << "ms\n";
}