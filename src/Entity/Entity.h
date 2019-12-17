/**
 * @file Entity.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the Entity class
 */

#ifndef PROJECT_SPACE_INVADERS_ENTITY_H
#define PROJECT_SPACE_INVADERS_ENTITY_H

#include <string>

#include "../Observer.h"

class Observer;

class Entity : public Observer {
protected:
    std::string image;

public:
    Entity();

protected:

    Entity(const std::string& image);

    virtual void onNotify(Utils::Event event);
};

#endif //PROJECT_SPACE_INVADERS_ENTITY_H
