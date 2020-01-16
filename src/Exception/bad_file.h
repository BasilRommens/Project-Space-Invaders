/**
 * @file bad_file.h
 * @author Basil Rommens
 * @date 1/16/20
 * @brief The header file of the class bad_file
 */

#ifndef PROJECT_SPACE_INVADERS_BAD_FILE_H
#define PROJECT_SPACE_INVADERS_BAD_FILE_H

#include <exception>

class bad_file : public std::exception {
private:
    const char* info;
public:
    const char* what() const noexcept;

    explicit bad_file(const char* message);
};

#endif //PROJECT_SPACE_INVADERS_BAD_FILE_H
