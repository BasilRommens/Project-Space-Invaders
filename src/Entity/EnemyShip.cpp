/**
 * @file EnemyShip.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the class EnemyShip
 */

#include "EnemyShip.h"

void EntityNS::EnemyShip::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    if (Utils::Event::UNMOVE==event and moved) {
        // Set all the ships to not having moved such that the next tick the enemy ship can move
        for (auto ship: otherShips) {
            ship.lock()->moved = false;
        }
    }
    else if (event==Utils::Event::DECREASE_DELAY) {
        decreaseDelay();
        if (currentDelay==0) {
            // create new delay
            currentDelay = bulletDelay+randomOffset();
            // Fire a bullet
            notify(shared_from_this(), Utils::Event::FIRE_BULLET);
        }
    }

    // Return if the entity passed through isnt this one
    if (moved) {
        return;
    }

    // We need to draw update all the ships if every one of them has moved
    // Is outside of the switch statement because it doesnt work there
    bool notAllMoved = false;

    switch (event) {
    case Utils::Event::MOVE:
        if (direction==Utils::Direction::LEFT) {
            std::cout << "left move" << std::endl;
            moveLeft();
        }
        else {
            std::cout << "right move" << std::endl;
            moveRight();
        }

        for (auto ship: otherShips) {
            if (not ship.lock()->moved) {
                notAllMoved = true;
            }
        }
        // If all the ships have been moved then draw all of them
        if (not notAllMoved) {
            for (auto ship: otherShips) {
                ship.lock()->notify(ship.lock(), Utils::Event::UPDATE_DRAW);
            }
        }
        break;
    default:
        std::cout << "default triggered" << std::endl;
    }
}

void EntityNS::EnemyShip::moveRight()
{
    moved = true;
    // Keep track of the distance covered by the ship
    double prevPos = pos.getX();
    pos.moveXPos(-HSpeed, hitbox);
    double newPos = pos.getX();
    auto newDistance = std::abs(prevPos-newPos);
    // begin to move all the ships if the travelled distance is smaller than the
    if (newDistance<HSpeed*.98) {
        distance = newDistance;
        // Update all the ships with the new distance
        for (const std::weak_ptr<EnemyShip> ship: otherShips) {
            swapDirection(ship.lock());
            // Move every ship down because we hit the end of the map
            ship.lock()->pos.moveYPos(-VSpeed, hitbox);
            if (ship.lock().get()==this) {
                continue;
            }
            if (ship.lock()->moved) {
                // Move back the distance thats done too much according to this ship
                ship.lock()->pos.moveXPos(HSpeed-distance, hitbox);
            }
            else {
                // Move the not yet moved ships the distance that this ship has moved
                ship.lock()->pos.moveXPos(distance, hitbox);
            }
            // Set moved to true such that the observer pattern will not update the ship again
            ship.lock()->moved = true;
        }
    }
}

void EntityNS::EnemyShip::moveLeft()
{
    moved = true;
    // Keep track of the distance covered by the ship
    double prevPos = pos.getX();
    pos.moveXPos(HSpeed, hitbox);
    double newPos = pos.getX();
    auto newDistance = std::abs(prevPos-newPos);
    // begin to move all the ships if the travelled distance is smaller than the
    if (newDistance<HSpeed*.98) {
        distance = newDistance;
        // Update all the ships with the new distance
        for (const std::weak_ptr<EnemyShip> ship: otherShips) {
            swapDirection(ship.lock());
            // Move every ship down because we hit the end of the map
            ship.lock()->pos.moveYPos(-VSpeed, hitbox);
            if (ship.lock().get()==this) {
                continue;
            }
            if (ship.lock()->moved) {
                // Move back the distance thats done too much according to this ship
                ship.lock()->pos.moveXPos(distance-HSpeed, hitbox);
            }
            else {
                // Move the not yet moved ships the distance that this ship has moved
                ship.lock()->pos.moveXPos(-distance, hitbox);
            }
            // Set moved to true such that the observer pattern will not update the ship again
            ship.lock()->moved = true;
        }
    }
}

void EntityNS::EnemyShip::fireBullet()
{

}

std::string EntityNS::EnemyShip::getType() const
{
    return "enemy";
}

EntityNS::EnemyShip::~EnemyShip()
{

}

double EntityNS::EnemyShip::getDistance() const
{
    return distance;
}

inline void EntityNS::EnemyShip::swapDirection(std::shared_ptr<EnemyShip> ship)
{
    if (ship->direction==Utils::Direction::LEFT) {
        ship->direction = Utils::Direction::RIGHT;
    }
    else {
        ship->direction = Utils::Direction::LEFT;
    }
}

void EntityNS::EnemyShip::addShip(std::weak_ptr<EnemyShip> ship)
{
    otherShips.push_back(ship);
}

int EntityNS::EnemyShip::randomOffset()
{
    // half the Framerate * amount of ships + randRange(0, 360)
    return 60/2*(int) otherShips.size()+(int) random()%360;
}

EntityNS::EnemyShip::EnemyShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
        int bulletDelay, const Hitbox& hitbox, double vSpeed)
        :Ship(image, pos, health, hSpeed, bulletDelay, hitbox), VSpeed(vSpeed)
{
    moved = false;
    currentDelay += randomOffset();
}