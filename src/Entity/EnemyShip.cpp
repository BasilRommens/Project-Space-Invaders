/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#include "EnemyShip.h"

EnemyShip::EnemyShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double vSpeed)
        :Ship(image, pos, health, hSpeed), VSpeed(vSpeed) { }
