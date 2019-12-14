/**
 * @file Stopwatch.h
 * @author Basil Rommens
 * @date 12/11/19
 * @brief The header file of the Stopwatch class
 * @source https://www.tutorialspoint.com/Explain-Cplusplus-Singleton-design-pattern
 */

#ifndef PROJECT_SPACE_INVADERS_STOPWATCH_H
#define PROJECT_SPACE_INVADERS_STOPWATCH_H

#include <chrono>

class Stopwatch {
private:
    static Stopwatch instance; /** @var instance: The sole instance of the Stopwatch class */
    std::chrono::time_point<std::chrono::system_clock> startTime{}; /** @var startTime: The time at which the stopwatch object is started */
    std::chrono::time_point<std::chrono::system_clock> stopTime{}; /** @var stopTime: The time at which the stopwatch object is stopped */

    /**
     * @brief The default constructor of Stopwatch
     */
    Stopwatch();

public:
    /**
     * @brief sets the timepoint at which it starts at the current time
     */
    void start();

    /**
     *
     * @return the duration from the start time to the current time without changing the stop time
     */
    std::chrono::duration<double> get_lap() const;

    /**
     * @brief sets the stop time of the stopwatch to the current time
     */
    void stop();

    /**
     *
     * @return the duration from the start time to the stop time
     */
    std::chrono::duration<double> getTotalDif() const;

    /**
     * @brief resets the stopwatch by setting the start time to the current time
     */
    void reset();

    /**
     * @return The sole instance of an object of this class
     */
    static Stopwatch getStopwatch();
};

#endif //PROJECT_SPACE_INVADERS_STOPWATCH_H
