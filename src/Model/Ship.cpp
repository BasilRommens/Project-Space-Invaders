/**
 * @file Ship.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the class Ship
 */

#include "Ship.h"
#include "World.h"

std::string Model::Ship::getType() const { return ""; }

std::shared_ptr<Utils::Position> Model::Ship::getPos() const { return std::make_shared<Utils::Position>(pos); }

void Model::Ship::setPosition(Utils::Position newPos) { pos.setPosition(newPos); }

Model::Ship::~Ship() { dummyBullet.reset(); }

void Model::Ship::resetDelay() { currentDelay = bulletDelay; }

void Model::Ship::decreaseDelay()
{
        if (currentDelay != 0) {
                --currentDelay;
        }
}

Model::Ship::Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed, int bulletDelay,
                  const Utils::Hitbox& hitbox, Model::World& world)
    : Entity(image), pos(pos), health(health), HSpeed(hSpeed), hitbox(hitbox), bulletDelay(bulletDelay), world(world)
{
        // TODO add exception
        currentDelay = 0;
}

const Utils::Hitbox& Model::Ship::getHitbox() const { return hitbox; }

void Model::Ship::addBullet(std::shared_ptr<Bullet> dummyBullet) { this->dummyBullet = dummyBullet; }

std::shared_ptr<Model::Entity> Model::Ship::spawnBullet() const
{
        Bullet newBullet(dummyBullet);
        return std::make_shared<Bullet>(newBullet);
}

std::shared_ptr<Model::Bullet> Model::Ship::getDummyBullet() const { return dummyBullet; }

void Model::Ship::doDamage(double damage) { health -= damage; }

bool Model::Ship::collidable() const { return true; }

double Model::Ship::getHealth() const { return health; }

int Model::Ship::getCurrentDelay() const { return currentDelay; }
