/**
 * @file 
 * @author Basil Rommens
 * @date 12/11/19
 * @brief ...
 */

#include "Stopwatch.h"

void Stopwatch::start()
{
    startTime = std::chrono::system_clock::now();
}

std::chrono::duration<double> Stopwatch::get_lap() const
{
    auto test = std::chrono::system_clock::now();
    return std::chrono::system_clock::now()-startTime;
}

void Stopwatch::stop()
{
    stopTime = std::chrono::system_clock::now();
}

std::chrono::duration<double> Stopwatch::getTotalDif() const
{
    return startTime-stopTime;
}

void Stopwatch::reset()
{
    start();
}

Stopwatch Stopwatch::getStopwatch()
{
    static Stopwatch instance;
    return instance;
}

Stopwatch::Stopwatch()
        :startTime(std::chrono::system_clock::now()) { }
