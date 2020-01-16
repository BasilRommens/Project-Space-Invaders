/**
 * @file entity_underflow.cpp
 * @author Basil Rommens
 * @date 1/16/20
 * @brief The cpp file of the class entity_underflow
 */

#include "entity_underflow.h"

Exception::entity_underflow::entity_underflow(const char* message)
{
    info = message;
}

const char* Exception::entity_underflow::what() const noexcept
{
    return info;
}