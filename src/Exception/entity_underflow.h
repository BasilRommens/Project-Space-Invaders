/**
 * @file entity_underflow.h
 * @author Basil Rommens
 * @date 1/16/20
 * @brief The header file of the class entity_underflow
 */

#ifndef PROJECT_SPACE_INVADERS_ENTITY_UNDERFLOW_H
#define PROJECT_SPACE_INVADERS_ENTITY_UNDERFLOW_H

#include <exception>

namespace Exception {

    class entity_underflow : public std::exception {
    private:
        const char* info; ///< Variable that keeps the info about the error that occurred
    public:
        /**
         * @return The info about the error that occurred
         */
        const char* what() const noexcept;

        /**
         * @brief makes a new object of the type entity_underflow
         * @param message: The message that keeps the info about the exception
         */
        explicit entity_underflow(const char* message);
    };

}

#endif //PROJECT_SPACE_INVADERS_ENTITY_UNDERFLOW_H
