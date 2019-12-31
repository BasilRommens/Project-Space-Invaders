#include "PlayerShip.h"

/**
 * @file
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

Model::PlayerShip::PlayerShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
        int bulletDelay, const Hitbox& hitbox)
        :Ship(image, pos, health, hSpeed, bulletDelay, hitbox) { }

void Model::PlayerShip::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
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
        if (not currentDelay) {
            notify(shared_from_this(), Utils::Event::FIRE_BULLET);
            resetDelay(); // reset currentDelay
        }
        break;
    default:
        break;
    }
}

void Model::PlayerShip::moveRight()
{
    pos.moveXPos(HSpeed, hitbox);
}

void Model::PlayerShip::moveLeft()
{
    pos.moveXPos(-HSpeed, hitbox);
}

std::string Model::PlayerShip::getType() const
{
    return "player";
}

Model::PlayerShip::~PlayerShip()
{

}

void Model::PlayerShip::fireBullet()
{

}
