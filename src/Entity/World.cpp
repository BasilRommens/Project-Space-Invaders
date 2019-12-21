/**
 * @file World.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the World class
 */

#include "World.h"
#include "Ship.h"

void World::addEntity(std::shared_ptr<Entity> entity)
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

void World::removeEntity(std::shared_ptr<Entity> entity)
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

World::World(const std::string& image)
        :Entity(image) { }

World::World() { }

const std::vector<std::shared_ptr<Entity>>& World::getEntities() const
{
    return entities;
}

std::shared_ptr<Entity> World::getPlayer() const
{
    for (auto entity: entities) {
        std::string type = entity->getType();
        if (type=="player") {
            return entity;
        }
    }
    return nullptr;
}

std::string World::getType() const
{
    return "world";
}

void World::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    // TODO throw error when no entity is detected
    switch (event) {
    case Utils::Event::FIRE_BULLET:
        std::cout << "create" << std::endl;
        // Create a bullet with that needs to depart from the certain ship
        this->addEntity(createBullet(entity));
        break;
    default:
        std::cout << "Default" << std::endl;
    }
}

std::shared_ptr<Entity> World::createBullet(std::shared_ptr<Entity> ship)
{
    // TODO add data to the bullet
    std::shared_ptr<Entity> bullet;
    return bullet;
}
