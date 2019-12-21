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

void PlayerShip::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    // Notify if we need to close the window
    if (not entity and event==Utils::Event::CLOSE_WINDOW) {
        notify(nullptr, event);
    }

    // Return if the entity passed through isnt this one
    if (entity.get()!=this) {
        return;
    }

    switch (event) {
    case Utils::Event::MOVE_RIGHT:
        // TODO move right according to speed
        std::cout << "right move" << std::endl;
        moveRight();
        notify(shared_from_this(), Utils::Event::UPDATE_DRAW);
        break;
    case Utils::Event::MOVE_LEFT:
        // TODO move left according to speed
        std::cout << "left move" << std::endl;
        moveLeft();
        notify(shared_from_this(), Utils::Event::UPDATE_DRAW);
        break;
    case Utils::Event::FIRE_BULLET:
        std::cout << "fire bullet" << std::endl;
        fireBullet();
        break;
    default:
        std::cout << "default triggered" << std::endl;
    }
}

void PlayerShip::moveRight()
{
    pos.moveXPos(HSpeed);
}

void PlayerShip::moveLeft()
{
    pos.moveXPos(-HSpeed);
}

void PlayerShip::fireBullet()
{
    notify(shared_from_this(), Utils::Event::FIRE_BULLET);
}

std::string PlayerShip::getType() const
{
    return "player";
}
