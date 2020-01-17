/**
 * @file bad_type.h
 * @author Basil Rommens
 * @date 1/16/20
 * @brief The header file of the class bad_type
 * @see https://peterforgacs.github.io/2017/06/25/Custom-C-Exceptions-For-Beginners/ (on 16/01/2020)
 */

#ifndef PROJECT_SPACE_INVADERS_BAD_TYPE_H
#define PROJECT_SPACE_INVADERS_BAD_TYPE_H

#include <exception>

/**
 * @addtogroup Exception
 * @{
 */
namespace Exception {

/**
 * @brief You can throw an exception of this type when the type you have used is not of the correct type
 */
class bad_type : public std::exception
{
private:
        const char* info; ///< Variable that keeps the info about the error that occurred
public:
        /**
         * @return The info about the error that occurred
         */
        const char* what() const noexcept;

        /**
         * @brief makes a new object of the type bad_type
         * @param message: The message that keeps the info about the exception
         */
        explicit bad_type(const char* message);
};

} // namespace Exception
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_BAD_TYPE_H
