#include "Timer.h"
#include <iostream>
#include "Log.h"

Timer::Timer(std::string fctName)
    : fctName(fctName)
{
    //Start the timer (set the start variable)
    start = HrClock::now();
}

Timer::~Timer(){
    //End the timer (set a TPoint end variable)
    TPoint end = HrClock::now();
    //Calculate the elaspe time
    eTime elaspeTime = end - start;
    //Convert the elaspe time to ms
    float ms = elaspeTime.count() * 1000;
    //Output the elaspe time.
    CORE_INFO(fctName, " took: ", ms, "ms to execute");
}