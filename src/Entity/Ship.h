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

class Hitbox;

class Ship : public Entity {
private:
    Position pos;
    double health;
    Hitbox hitbox;
    double speed;
};

#endif //PROJECT_SPACE_INVADERS_SHIP_H
