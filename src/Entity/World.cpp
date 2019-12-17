/**
 * @file World.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the World class
 */

#include "World.h"

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
