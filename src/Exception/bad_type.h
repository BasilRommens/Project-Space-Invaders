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

// TODO add documentation
class bad_type : public std::exception {
private:
    const char* info;
public:
    const char* what() const noexcept;

    explicit bad_type(const char* message);
};

#endif //PROJECT_SPACE_INVADERS_BAD_TYPE_H
