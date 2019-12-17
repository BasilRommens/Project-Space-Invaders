/**
 * @file Ship.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the class Ship
 */

#ifndef PROJECT_SPACE_INVADERS_SHIP_H
#define PROJECT_SPACE_INVADERS_SHIP_H

#include "Entity.h"
#include "../utils/Position.h"

class Ship : public Entity {
private:
    Utils::Position pos;
    double health;
    double HSpeed;
public:
    Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed);
};

#endif //PROJECT_SPACE_INVADERS_SHIP_H
