/**
 * @file 
 * @author Basil Rommens
 * @date 12/11/19
 * @brief ...
 */

#include "Stopwatch.h"

void Utils::Stopwatch::start()
{
    startTime = std::chrono::system_clock::now();
}

std::chrono::duration<double> Utils::Stopwatch::get_lap() const
{
    auto test = std::chrono::system_clock::now();
    return std::chrono::system_clock::now()-startTime;
}

void Utils::Stopwatch::stop()
{
    stopTime = std::chrono::system_clock::now();
}

std::chrono::duration<double> Utils::Stopwatch::getTotalDif() const
{
    return startTime-stopTime;
}

void Utils::Stopwatch::reset()
{
    start();
}

Utils::Stopwatch Utils::Stopwatch::getStopwatch()
{
    static Stopwatch instance;
    return instance;
}

Utils::Stopwatch::Stopwatch()
        :startTime(std::chrono::system_clock::now()) { }
