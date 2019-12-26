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
        :Ship(image, pos, health, hSpeed, damage), VSpeed(vSpeed)
{
    //std::weak_ptr<EnemyShip> weakEnemy = std::make_shared<EnemyShip>(*this);
    //otherShips.push_back(weakEnemy);
    moved = false;
}

void EntityNS::EnemyShip::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    if (Utils::Event::UNMOVE==event and moved) {
        // Set all the ships to not having moved such that the next tick the enemy ship can move
        for (auto ship: otherShips) {
            ship.lock()->moved = false;
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
                ship.lock()->moved = true;
            }
        }
        // If all the ships have been moved then draw all of them
        if (not notAllMoved) {
            for (auto ship: otherShips) {
                ship.lock()->notify(ship.lock(), Utils::Event::UPDATE_DRAW);
                ship.lock()->moved = true; // set it to true so that the notify of the observer pattern wouldnt happen twice
            }
        }
        break;
    case Utils::Event::FIRE_BULLET:
        // TODO add what to do when to fire a bullet
        std::cout << "fire bullet" << std::endl;
        fireBullet();
        break;
    default:
        std::cout << "default triggered" << std::endl;
    }
}

void EntityNS::EnemyShip::moveRight()
{
    moved = true;
    // Keep track of the distance covered by the ship
    auto prevPos = pos;
    pos.moveXPos(-HSpeed);
    auto newPos = pos;
    auto newDistance = newPos.getX()-prevPos.getX();
    // begin to move all the ships if the travelled distance is smaller than the
    if (newDistance<HSpeed) {
        distance = newDistance;
        // Update all the ships with the new distance
        for (const std::weak_ptr<EnemyShip> ship: otherShips) {
            swapDirection(ship.lock());
            // Move every ship down because we hit the end of the map
            ship.lock()->pos.moveYPos(-VSpeed);
            if (ship.lock().get()==this) {
                continue;
            }
            if (ship.lock()->moved) {
                // Move back the distance thats done too much according to this ship
                ship.lock()->pos.moveXPos(HSpeed-distance);
            }
            else {
                // Move the not yet moved ships the distance that this ship has moved
                ship.lock()->pos.moveXPos(distance);
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
    auto prevPos = pos;
    pos.moveXPos(HSpeed);
    auto newPos = pos;
    auto newDistance = prevPos.getX()-newPos.getX();
    // begin to move all the ships if the travelled distance is smaller than the
    if (newDistance<HSpeed) {
        distance = newDistance;
        // Update all the ships with the new distance
        for (const std::weak_ptr<EnemyShip> ship: otherShips) {
            swapDirection(ship.lock());
            // Move every ship down because we hit the end of the map
            ship.lock()->pos.moveYPos(-VSpeed);
            if (ship.lock().get()==this) {
                ship.lock()->notify(ship.lock(), Utils::Event::UPDATE_DRAW);
                continue;
            }
            if (ship.lock()->moved) {
                // Move back the distance thats done too much according to this ship
                ship.lock()->pos.moveXPos(distance-HSpeed);
            }
            else {
                // Move the not yet moved ships the distance that this ship has moved
                ship.lock()->pos.moveXPos(-distance);
            }
            // Set moved to true such that the observer pattern will not update the ship again
            ship.lock()->moved = true;
            ship.lock()->notify(ship.lock(), Utils::Event::UPDATE_DRAW);
        }
    }
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

EntityNS::EnemyShip::~EnemyShip()
{

}

double EntityNS::EnemyShip::getDistance() const
{
    return distance;
}

inline void EntityNS::EnemyShip::swapDirection(std::shared_ptr<EnemyShip> ship)
{
    if (direction==Utils::Direction::LEFT) {
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