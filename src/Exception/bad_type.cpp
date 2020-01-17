/**
 * @file bad_type.cpp
 * @author Basil Rommens
 * @date 1/16/20
 * @brief The cpp file of the class bad_type
 */

#include "bad_type.h"

Exception::bad_type::bad_type(const char* message) { info = message; }

const char* Exception::bad_type::what() const noexcept { return info; }
