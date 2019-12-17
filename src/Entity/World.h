/**
 * @file World.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the World class
 */

#ifndef PROJECT_SPACE_INVADERS_WORLD_H
#define PROJECT_SPACE_INVADERS_WORLD_H

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#include "Entity.h"

class World : public Entity {
private:
    std::vector<std::shared_ptr<Entity>> entities;
public:
    void addEntity(std::shared_ptr<Entity> entity);

    void removeEntity(std::shared_ptr<Entity> entity);

    World(const std::string& image);
};

#endif //PROJECT_SPACE_INVADERS_WORLD_H
