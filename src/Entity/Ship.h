/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_SHIP_H
#define PROJECT_SPACE_INVADERS_SHIP_H

#include "Entity.h"
#include "../utils/Position.h"
#include "../Observer.h"

class Ship : public Entity, public Observer {
private:
    Utils::Position pos;
    double health;
    double HSpeed;
};

#endif //PROJECT_SPACE_INVADERS_SHIP_H
