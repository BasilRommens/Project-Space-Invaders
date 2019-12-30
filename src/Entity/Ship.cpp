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

EntityNS::Ship::Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
        int bulletDelay, const Hitbox& hitbox)
        :Entity(image), pos(pos), health(health), HSpeed(hSpeed), hitbox(hitbox), bulletDelay(bulletDelay) { }

const Hitbox& EntityNS::Ship::getHitbox() const
{
    return hitbox;
}

void EntityNS::Ship::addBullet(std::shared_ptr<Bullet> dummyBullet)
{
    this->dummyBullet = dummyBullet;
}

std::shared_ptr<EntityNS::Entity> EntityNS::Ship::spawnBullet()
{
    Bullet newBullet(dummyBullet);
    return std::make_shared<Bullet>(newBullet);
}

std::shared_ptr<EntityNS::Bullet> EntityNS::Ship::getDummyBullet() const
{
    return dummyBullet;
}
