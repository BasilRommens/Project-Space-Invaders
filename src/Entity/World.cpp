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
        std::shared_ptr<Entity> bullet = entity->spawnBullet();
        this->addEntity(bullet);
        notify(bullet, Utils::Event::NEW_DRAW);
    }
}

EntityNS::World::~World()
{

}
