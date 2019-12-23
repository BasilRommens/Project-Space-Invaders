/**
 * @file World.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the World class
 */

#include "World.h"

void EntityNS::World::addEntity(std::shared_ptr<Entity> entity)
{
    try {
        if (!entity) {
            throw std::invalid_argument(
                    "No observer has been passed through in the method addObserver from the class Subject");
        }
        entities.push_back(entity);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void EntityNS::World::removeEntity(std::shared_ptr<Entity> entity)
{
    try {
        if (!entity) {
            throw std::invalid_argument(
                    "No observer has been passed through in the method removeObserver from the class Subject");
        }
        entities.erase(std::find(entities.begin(), entities.end(), entity));
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

EntityNS::World::World(const std::string& image)
        :Entity(image) { }

EntityNS::World::World() { }

const std::vector<std::shared_ptr<EntityNS::Entity>>& EntityNS::World::getEntities() const
{
    return entities;
}

std::shared_ptr<EntityNS::Entity> EntityNS::World::getPlayer() const
{
    for (auto entity: entities) {
        std::string type = entity->getType();
        if (type=="player") {
            return entity;
        }
    }
    return nullptr;
}

std::string EntityNS::World::getType() const
{
    return "world";
}

void EntityNS::World::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{

    // TODO throw error when no entity is detected
    if (event==Utils::Event::FIRE_BULLET) {
        // Create a bullet with that needs to depart from the certain ship
        std::shared_ptr<Entity> bullet = createBullet(entity);
        this->addEntity(bullet);
        notify(bullet, Utils::Event::NEW_DRAW);
    }
}

std::shared_ptr<EntityNS::Entity> EntityNS::World::createBullet(std::shared_ptr<Entity> ship)
{
    // TODO remove fixed image of the bullet
    // TODO remove fixed bullet speed
    // TODO fix the spawning position of the bullet
    Utils::Position pos(ship->getPos()->getX(), ship->getPos()->getY());
    std::string image("img/laser.png");
    Utils::Direction direction = (ship->getType()=="player") ? Utils::Direction::UP : Utils::Direction::DOWN;
    double speed = 0.05;
    double damage = ship->getDamage();
    std::shared_ptr<Entity> bullet(new Bullet(image, direction, speed, damage, pos, ship));

    // add the observer to be able to draw a bullet
    bullet->addObserver(ship->getDrawShared());
    return bullet;
}

EntityNS::World::~World()
{

}
