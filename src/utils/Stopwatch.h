/**
 * @file 
 * @author Basil Rommens
 * @date 12/11/19
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_STOPWATCH_H
#define PROJECT_SPACE_INVADERS_STOPWATCH_H

#include <chrono>

// TODO make singleton pattern of them
class Stopwatch {
private:
    static Stopwatch* instance;
    std::chrono::time_point<std::chrono::system_clock> startTime{};
    std::chrono::time_point<std::chrono::system_clock> stopTime{};

    Stopwatch();

public:
    void start();

    std::chrono::time_point<std::chrono::system_clock> get_start_time() const;

    std::chrono::duration<double> get_lap() const;

    void stop();

    std::chrono::duration<double> getTotalDif() const;

    void reset();

    static Stopwatch* getStopwatch();
};

#endif //PROJECT_SPACE_INVADERS_STOPWATCH_H
