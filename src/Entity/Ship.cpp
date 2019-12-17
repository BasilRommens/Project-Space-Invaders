/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#include "Ship.h"

Ship::Ship(const Utils::Position& pos, double health, double hSpeed)
        :pos(pos), health(health), HSpeed(hSpeed) { }

Ship::Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed)
        :Entity(image), pos(pos), health(health), HSpeed(hSpeed) { }
