/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#include "Ship.h"

Ship::Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double damage)
        :Entity(image), pos(pos), health(health), HSpeed(hSpeed), damage(damage) { }

std::string Ship::getType() const
{
    return "";
}

Utils::Position Ship::getPos() const
{
    return pos;
}

double Ship::getDamage() const
{
    return damage;
}
