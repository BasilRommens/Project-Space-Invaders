/**
 * @file bad_file.h
 * @author Basil Rommens
 * @date 1/16/20
 * @brief The header file of the class bad_file
 */

#ifndef PROJECT_SPACE_INVADERS_BAD_FILE_H
#define PROJECT_SPACE_INVADERS_BAD_FILE_H

#include <exception>

/**
 * @namespace Exception The namespace indicates all the classes that are supposed to be thrown as exceptions
 */

/**
 * @addtogroup Exception
 * @{
 */
namespace Exception {

    /**
     * @brief this exception can be used when a file is corrupted or wrongly formatted, just something with a file
     */
    class bad_file : public std::exception {
    private:
        const char* info; ///< Variable that keeps the info about the error that occurred
    public:
        /**
         * @return The info about the error that occurred
         */
        const char* what() const noexcept;

        /**
         * @brief makes a new object of the type bad_file
         * @param message: The message that keeps the info about the exception
         */
        explicit bad_file(const char* message);
    };

}
/**
 * @}
 */

#endif //PROJECT_SPACE_INVADERS_BAD_FILE_H
