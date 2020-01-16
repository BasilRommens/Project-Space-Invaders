/**
 * @file entity_underflow.h
 * @author Basil Rommens
 * @date 1/16/20
 * @brief The header file of the class entity_underflow
 */

#ifndef PROJECT_SPACE_INVADERS_ENTITY_UNDERFLOW_H
#define PROJECT_SPACE_INVADERS_ENTITY_UNDERFLOW_H

#include <exception>

// TODO add documentation
class entity_underflow : public std::exception {
private:
    const char* info;
public:
    const char* what() const noexcept;

    explicit entity_underflow(const char* message);
};

#endif //PROJECT_SPACE_INVADERS_ENTITY_UNDERFLOW_H
