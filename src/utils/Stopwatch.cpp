/**
 * @file 
 * @author Basil Rommens
 * @date 12/11/19
 * @brief ...
 */

#include "Stopwatch.h"

std::shared_ptr<Utils::Stopwatch> Utils::Stopwatch::instance = nullptr;

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

std::shared_ptr<Utils::Stopwatch>& Utils::Stopwatch::getStopwatch()
{
    if (!instance) {
        instance = std::make_shared<Stopwatch>(Stopwatch());
    }
    return instance;
}

Utils::Stopwatch::Stopwatch()
        :startTime(std::chrono::system_clock::now()) { }