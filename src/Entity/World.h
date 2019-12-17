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

#include "Entity.h"
#include "../Observer.h"

class World : public Entity, public Observer {
private:
    std::vector<std::shared_ptr<Entity>> Entities;
};

#endif //PROJECT_SPACE_INVADERS_WORLD_H
