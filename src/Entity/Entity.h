/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_ENTITY_H
#define PROJECT_SPACE_INVADERS_ENTITY_H

#include <string>
#include "../Observer.h"

class Entity : public Observer {
protected:
    std::string image;
    Entity(const std::string& image);
    virtual void onNotify(Event event) { }
};

#endif //PROJECT_SPACE_INVADERS_ENTITY_H
