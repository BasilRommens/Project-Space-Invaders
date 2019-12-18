/**
 * @file Ship.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the class Ship
 */

#ifndef PROJECT_SPACE_INVADERS_SHIP_H
#define PROJECT_SPACE_INVADERS_SHIP_H

#include <iostream>

#include "Entity.h"
#include "../utils/Position.h"

class Ship : public Entity {
protected:
    Utils::Position pos;
    double health;
    double HSpeed;
    double damage;

    virtual void moveRight() = 0;

    virtual void moveLeft() = 0;

    virtual void fireBullet() = 0;

public:
    Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double damage);
};

#endif //PROJECT_SPACE_INVADERS_SHIP_H
