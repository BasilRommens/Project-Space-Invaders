/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_PLAYERSHIP_H
#define PROJECT_SPACE_INVADERS_PLAYERSHIP_H

#include "Ship.h"

class PlayerShip : public Ship {
public:
    PlayerShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed);
};

#endif //PROJECT_SPACE_INVADERS_PLAYERSHIP_H
