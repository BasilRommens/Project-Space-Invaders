/**
 * @file Stopwatch.h
 * @author Basil Rommens
 * @date 12/11/19
 * @brief The header file of the Stopwatch class
 * @see [singleton pattern](https://stackoverflow.com/questions/47558290/singleton-class-with-smart-pointers-and-destructor-being-called)
 */

#ifndef PROJECT_SPACE_INVADERS_STOPWATCH_H
#define PROJECT_SPACE_INVADERS_STOPWATCH_H

#include <chrono>
#include <memory>

/**
 * @addtogroup Utils
 * @{
 */
namespace Utils {

    const double frameDuration = 1.0/60.0*1000000.0; ///< The duration of 1 frame

    /**
     * @brief The class that is implemented to be used as a stopwatch
     * @details The class is implemented as a singleton pattern
     * @see [Singleton pattern](https://stackoverflow.com/questions/47558290/singleton-class-with-smart-pointers-and-destructor-being-called)
     */
    class Stopwatch {
    private:
        static std::shared_ptr<Stopwatch> instance; ///< The sole instance of the Stopwatch class
        std::chrono::time_point<std::chrono::system_clock> startTime{}; ///< The time at which the stopwatch object is started
        std::chrono::time_point<std::chrono::system_clock> stopTime{}; ///< The time at which the stopwatch object is stopped

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
        static std::shared_ptr<Stopwatch>& getStopwatch();
    };

}

/**
 * @}
 */

#endif //PROJECT_SPACE_INVADERS_STOPWATCH_H
