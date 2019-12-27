/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#include "PlayerShip.h"

EntityNS::PlayerShip::PlayerShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
        double damage)
        :Ship(image, pos, health, hSpeed, damage) { }

void EntityNS::PlayerShip::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
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
        moveRight();
        notify(shared_from_this(), Utils::Event::UPDATE_DRAW);
        break;
    case Utils::Event::MOVE_LEFT:
        moveLeft();
        notify(shared_from_this(), Utils::Event::UPDATE_DRAW);
        break;
    case Utils::Event::FIRE_BULLET:
        std::cout << "fire bullet" << std::endl;
        notify(shared_from_this(), Utils::Event::FIRE_BULLET);
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
