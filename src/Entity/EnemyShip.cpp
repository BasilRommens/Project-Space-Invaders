/**
 * @file EnemyShip.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the class EnemyShip
 */

#include "EnemyShip.h"

EntityNS::EnemyShip::EnemyShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
        double damage,
        double vSpeed)
        :Ship(image, pos, health, hSpeed, damage), VSpeed(vSpeed) { }

void EntityNS::EnemyShip::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    // Return if the entity passed through isnt this one
    if (entity.get()!=this) {
        return;
    }

    switch (event) {
    case Utils::Event::MOVE_RIGHT:
        // TODO move right according to speed
        std::cout << "right move" << std::endl;
        moveRight();
        break;
    case Utils::Event::MOVE_LEFT:
        // TODO move left according to speed
        std::cout << "left move" << std::endl;
        moveLeft();
        break;
    case Utils::Event::FIRE_BULLET:
        // TODO add what to do when firing a bullet
        std::cout << "fire bullet" << std::endl;
        break;
    default:
        std::cout << "default triggered" << std::endl;
    }
}

void EntityNS::EnemyShip::moveRight()
{
    pos.moveXPos(-HSpeed);
}

void EntityNS::EnemyShip::moveLeft()
{
    pos.moveXPos(HSpeed);
}

void EntityNS::EnemyShip::fireBullet()
{
    std::shared_ptr<Entity> p(this);
    notify(p, Utils::Event::FIRE_BULLET);
}

std::string EntityNS::EnemyShip::getType() const
{
    return "enemy";
}
