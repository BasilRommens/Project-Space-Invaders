/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#include "Ship.h"

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

EntityNS::Ship::~Ship()
{

}

void EntityNS::Ship::resetDelay()
{
    currentDelay = bulletDelay;
}

void EntityNS::Ship::decreaseDelay()
{
    if (currentDelay!=0) {
        --currentDelay;
    }
}

EntityNS::Ship::Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double damage,
        int bulletDelay, const Hitbox& hitbox, std::shared_ptr<Bullet> dummyBullet)
        :Entity(image), pos(pos), health(health), HSpeed(hSpeed), damage(damage), hitbox(hitbox),
         dummyBullet(std::move(dummyBullet)) { }
