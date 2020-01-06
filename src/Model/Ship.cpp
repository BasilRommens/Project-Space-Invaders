/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#include "Ship.h"
#include "World.h"

std::string Model::Ship::getType() const
{
    return "";
}

std::shared_ptr<Utils::Position> Model::Ship::getPos() const
{
    return std::make_shared<Utils::Position>(pos);
}

void Model::Ship::setPosition(Utils::Position newPos)
{
    pos.setPosition(newPos);
}

Model::Ship::~Ship()
{
    dummyBullet.reset();
}

void Model::Ship::resetDelay()
{
    currentDelay = bulletDelay;
}

void Model::Ship::decreaseDelay()
{
    if (currentDelay!=0) {
        --currentDelay;
    }
}

Model::Ship::Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
        int bulletDelay, const Utils::Hitbox& hitbox)
        :Entity(image), pos(pos), health(health), HSpeed(hSpeed), hitbox(hitbox), bulletDelay(bulletDelay)
{
    currentDelay = 0;
}

const Utils::Hitbox& Model::Ship::getHitbox() const
{
    return hitbox;
}

void Model::Ship::addBullet(std::shared_ptr<Bullet> dummyBullet)
{
    this->dummyBullet = dummyBullet;
}

std::shared_ptr<Model::Entity> Model::Ship::spawnBullet()
{
    Bullet newBullet(dummyBullet);
    return std::make_shared<Bullet>(newBullet);
}

std::shared_ptr<Model::Bullet> Model::Ship::getDummyBullet() const
{
    return dummyBullet;
}

void Model::Ship::doDamage(double damage)
{
    health -= damage;
}

bool Model::Ship::collidable() const
{
    return true;
}

double Model::Ship::getHealth() const
{
    return health;
}

int Model::Ship::getCurrentDelay() const
{
    return currentDelay;
}

void Model::Ship::addWorld(std::shared_ptr<Model::Entity> worldToAdd)
{
    // TODO check if the world to add is effective the world
    std::shared_ptr<Model::World> sharedWorld = std::static_pointer_cast<Model::World>(worldToAdd);
    world = sharedWorld; // assign the shared world to the weak pointer of the world
}
