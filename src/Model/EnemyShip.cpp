/**
 * @file EnemyShip.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the class EnemyShip
 */

#include "EnemyShip.h"

void Model::EnemyShip::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
        // TODO clean up function
        if (Utils::Event::REMOVE == event and entity.get() == this) {
                for (auto otherShip = otherShips.begin(); otherShip != otherShips.end(); ++otherShip) {
                        if ((*otherShip).lock().get() == this) {
                                otherShips.erase(otherShip);
                                break;
                        }
                }
        }
        if (Utils::Event::UNMOVE == event and moved) {
                // Set all the ships to not having moved such that the next tick the enemy ship can move
                for (const std::weak_ptr<EnemyShip> ship : otherShips) {
                        ship.lock()->moved = false;
                }
        } else if (event == Utils::Event::DECREASE_DELAY) {
                decreaseDelay();
                if (currentDelay == 0) {
                        // Fire a bullet
                        world.fireBullet(shared_from_this());
                        // create new delay
                        currentDelay = bulletDelay + randomOffset();
                }
        }

        // Return if the entity passed through isnt this one
        if (moved) {
                return;
        }

        // We need to draw update all the ships if every one of them has moved
        // Is outside of the switch statement because it doesnt work there
        bool notAllMoved = false;

        if (event == Utils::Event::MOVE) {
                if (direction == Utils::Direction::LEFT) {
                        moveLeft();
                } else {
                        moveRight();
                }

                for (const std::weak_ptr<EnemyShip> ship : otherShips) {
                        if (not ship.lock()->moved) {
                                notAllMoved = true;
                        }
                }
                // If all the ships have been moved then draw all of them
                if (not notAllMoved) {
                        for (const std::weak_ptr<EnemyShip> ship : otherShips) {
                                ship.lock()->notify(ship.lock(), Utils::Event::UPDATE_DRAW);
                        }
                }
        }
}

void Model::EnemyShip::moveRight()
{
        moved = true;
        // Keep track of the distance covered by the ship
        double prevPos = pos.getX();
        try {
                pos.moveXPos(HSpeed, hitbox);
        } catch (std::exception& e) {
                std::cout << "Enemyship hit the wall" << std::endl;
        }
        double newPos = pos.getX();
        auto newDistance = std::abs(prevPos - newPos);
        // begin to move all the ships if the travelled distance is smaller than the speed
        // (with a small offset to ensure floating point errors dont account for this distance)
        if (newDistance < HSpeed * .98) {
                distance = newDistance;
                // Update all the ships with the new distance
                for (const std::weak_ptr<EnemyShip> ship : otherShips) {
                        swapDirection(ship.lock());
                        // Move every ship down because we hit the end of the map
                        ship.lock()->pos.moveYPos(-VSpeed, hitbox);

                        // If the endline has been hit by one of the ships set the end of the world to true
                        if (world.hitEndLine(ship.lock())) {
                                world.setEnd(true);
                        }

                        if (ship.lock().get() == this) {
                                continue;
                        }
                        if (ship.lock()->moved) {
                                // Move back the distance thats done too much according to this ship
                                ship.lock()->pos.moveXPos(HSpeed - distance, hitbox);
                        } else {
                                // Move the not yet moved ships the distance that this ship has moved
                                ship.lock()->pos.moveXPos(distance, hitbox);
                        }
                        // Set moved to true such that the observer pattern will not update the ship again
                        ship.lock()->moved = true;
                }
                notify(shared_from_this(), Utils::Event::MOVED_DOWN);
        }
}

void Model::EnemyShip::moveLeft()
{
        moved = true;
        // Keep track of the distance covered by the ship
        double prevPos = pos.getX();
        try {
                pos.moveXPos(-HSpeed, hitbox);
        } catch (std::exception& e) {
                std::cout << "Enemyship hit the wall" << std::endl;
        }
        double newPos = pos.getX();
        auto newDistance = std::abs(prevPos - newPos);
        // begin to move all the ships if the travelled distance is smaller than the
        if (newDistance < HSpeed * .98) {
                distance = newDistance;
                // Update all the ships with the new distance
                for (const std::weak_ptr<EnemyShip> ship : otherShips) {
                        swapDirection(ship.lock());
                        // Move every ship down because we hit the end of the map
                        ship.lock()->pos.moveYPos(-VSpeed, hitbox);

                        // If the endline has been hit by one of the ships set the end of the world to true
                        if (world.hitEndLine(ship.lock())) {
                                world.setEnd(true);
                        }

                        if (ship.lock().get() == this) {
                                continue;
                        }
                        if (ship.lock()->moved) {
                                // Move back the distance thats done too much according to this ship
                                ship.lock()->pos.moveXPos(distance - HSpeed, hitbox);
                        } else {
                                // Move the not yet moved ships the distance that this ship has moved
                                ship.lock()->pos.moveXPos(-distance, hitbox);
                        }
                        // Set moved to true such that the observer pattern will not update the ship again
                        ship.lock()->moved = true;
                }
                notify(shared_from_this(), Utils::Event::MOVED_DOWN);
        }
}

std::string Model::EnemyShip::getType() const { return "enemy"; }

double Model::EnemyShip::getDistance() const { return distance; }

inline void Model::EnemyShip::swapDirection(std::shared_ptr<EnemyShip> ship) const
{
        // Swap the direction of the ship
        if (ship->direction == Utils::Direction::LEFT) {
                ship->direction = Utils::Direction::RIGHT;
        } else {
                ship->direction = Utils::Direction::LEFT;
        }
}

void Model::EnemyShip::addShip(std::weak_ptr<EnemyShip> ship) { otherShips.push_back(ship); }

inline int Model::EnemyShip::randomOffset() const
{
        // half the Framerate * amount of ships + randRange(0, 360)
        return 60 / 2 * (int)otherShips.size() + (int)random() % 360;
}

Model::EnemyShip::EnemyShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
                            int bulletDelay, const Utils::Hitbox& hitbox, double vSpeed, Model::World& world)
    : Ship(image, pos, health, hSpeed, bulletDelay, hitbox, world), VSpeed(vSpeed)
{
        moved = false;
        currentDelay += randomOffset();
}