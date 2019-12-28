#include "PlayerShip.h"

/**
 * @file
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

EntityNS::PlayerShip::PlayerShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
        double damage, int bulletDelay, const Hitbox& hitbox, std::shared_ptr<Bullet> dummyBullet)
        :Ship(image, pos, health, hSpeed, damage, bulletDelay, hitbox, dummyBullet) { }

void EntityNS::PlayerShip::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    // Notify if we need to close the window
    if (not entity and event==Utils::Event::CLOSE_WINDOW) {
        notify(nullptr, event);
    }

    if (not entity and event==Utils::Event::DECREASE_DELAY) {
        decreaseDelay();
    }

    // Return if the entity passed through isnt this one
    if (entity.get()!=this) {
        return;
    }

    switch (event) {
    case Utils::Event::MOVE_RIGHT:
        moveRight();
        notify(shared_from_this(), Utils::Event::UPDATE_DRAW);
        break;
    case Utils::Event::MOVE_LEFT:
        moveLeft();
        notify(shared_from_this(), Utils::Event::UPDATE_DRAW);
        break;
    case Utils::Event::FIRE_BULLET:
        std::cout << "fire bullet" << std::endl;
        if (not currentDelay) {
            notify(shared_from_this(), Utils::Event::FIRE_BULLET);
            resetDelay(); // reset currentDelay
        }
        break;
    default:
        std::cout << "default triggered" << std::endl;
    }
}

void EntityNS::PlayerShip::moveRight()
{
    pos.moveXPos(HSpeed);
}

void EntityNS::PlayerShip::moveLeft()
{
    pos.moveXPos(-HSpeed);
}

std::string EntityNS::PlayerShip::getType() const
{
    return "player";
}

EntityNS::PlayerShip::~PlayerShip()
{

}

void EntityNS::PlayerShip::fireBullet()
{

}
