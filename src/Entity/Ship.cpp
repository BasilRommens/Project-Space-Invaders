/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#include "Ship.h"

EntityNS::Ship::Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double damage)
        :Entity(image), pos(pos), health(health), HSpeed(hSpeed), damage(damage) { }

std::string EntityNS::Ship::getType() const
{
    return "";
}

std::shared_ptr<Utils::Position> EntityNS::Ship::getPos() const
{
    return std::make_shared<Utils::Position>(pos);
}

double EntityNS::Ship::getDamage() const
{
    return damage;
}

void EntityNS::Ship::setPosition(Utils::Position newPos)
{
    pos.setPosition(newPos);
}
