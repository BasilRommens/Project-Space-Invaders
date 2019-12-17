/**
 * @file Bullet.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the Bullet class
 */

#ifndef PROJECT_SPACE_INVADERS_BULLET_H
#define PROJECT_SPACE_INVADERS_BULLET_H

#include "Entity.h"
#include "../utils/Position.h"

class Bullet : public Entity {
private:
    Utils::Direction direction;
    double speed;
    double damage;
    Utils::Position pos;
};

#endif //PROJECT_SPACE_INVADERS_BULLET_H
