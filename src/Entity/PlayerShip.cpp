/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#include "PlayerShip.h"

PlayerShip::PlayerShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed)
        :Ship(image, pos, health, hSpeed) { }
