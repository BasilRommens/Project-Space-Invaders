/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_BULLET_H
#define PROJECT_SPACE_INVADERS_BULLET_H

#include "Entity.h"
#include "../utils/Position.h"

enum Direction {
    UP,
    DOWN
};

class Bullet : public Entity {
private:
    Direction direction;
    double speed;
    double damage;
    Utils::Position pos;
};

#endif //PROJECT_SPACE_INVADERS_BULLET_H
