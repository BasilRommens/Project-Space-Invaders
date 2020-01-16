/**
 * @file bad_file.cpp
 * @author Basil Rommens
 * @date 1/16/20
 * @brief The cpp file of the class bad_file
 */

#include "bad_file.h"

Exception::bad_file::bad_file(const char* message)
{
    info = message;
}

const char* Exception::bad_file::what() const noexcept
{
    return info;
}