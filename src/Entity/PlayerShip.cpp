/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#include "PlayerShip.h"

PlayerShip::PlayerShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
        double damage)
        :Ship(image, pos, health, hSpeed, damage) { }

void PlayerShip::onNotify(Utils::Event event)
{
    switch (event) {
    case Utils::Event::MOVE_RIGHT:
        // TODO move right according to speed
        std::cout << "right move" << std::endl;
        break;
    case Utils::Event::MOVE_LEFT:
        // TODO move left according to speed
        std::cout << "left move" << std::endl;
        break;
    case Utils::Event::FIRE_BULLET:
        // TODO add what to do when firing a bullet
        std::cout << "fire bullet" << std::endl;
        break;
    default:
        std::cout << "default triggered" << std::endl;
    }
}

void PlayerShip::moveRight()
{

}

void PlayerShip::moveLeft()
{

}

void PlayerShip::fireBullet()
{

}
