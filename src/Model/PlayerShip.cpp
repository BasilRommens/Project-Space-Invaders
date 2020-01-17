/**
 * @file PlayerShip.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of PlayerShip class
 */
#include "PlayerShip.h"

Model::PlayerShip::PlayerShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
                              int bulletDelay, const Utils::Hitbox& hitbox, Model::World& world)
    : Ship(image, pos, health, hSpeed, bulletDelay, hitbox, world)
{
}

void Model::PlayerShip::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
        // Notify if we need to close the window
        if (not entity and event == Utils::Event::CLOSE_WINDOW) {
                notify(nullptr, event);
        }

        if (not entity and event == Utils::Event::DECREASE_DELAY) {
                decreaseDelay();
        }

        // Return if the entity passed through isnt this one
        if (entity.get() != this) {
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
                        world.fireBullet(shared_from_this());
                        resetDelay(); // reset currentDelay
                }
                break;
        default:
                break;
        }
}

void Model::PlayerShip::moveRight()
{
        try {
                pos.moveXPos(HSpeed, hitbox);
        } catch (std::exception& e) { // This is a structure to detect if the player has hit the wall
        }
}

void Model::PlayerShip::moveLeft()
{
        try {
                pos.moveXPos(-HSpeed, hitbox);
        } catch (std::exception& e) { // This is a structure to detect if the player has hit the wall
        }
}

std::string Model::PlayerShip::getType() const { return "player"; }