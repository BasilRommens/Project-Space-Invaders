/**
 * @file 
 * @author Basil Rommens
 * @date 12/11/19
 * @brief ...
 */

#include "Stopwatch.h"

std::chrono::time_point<std::chrono::system_clock> Stopwatch::get_start_time() const
{
    return startTime;
}

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
