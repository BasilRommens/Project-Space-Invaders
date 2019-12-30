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
#include "Bullet.h"

namespace EntityNS {

// TODO add window sizes to the world
    class World : public EntityNS::Entity {
    private:
        std::vector<std::shared_ptr<EntityNS::Entity>> entities;

        bool areColliding(std::shared_ptr<Entity> thisEntity, std::shared_ptr<Entity> otherEntity);

        void handleColliding(std::shared_ptr<Entity> thisEntity, std::shared_ptr<Entity> otherEntity);

    public:
        virtual ~World();

        void addEntity(std::shared_ptr<EntityNS::Entity> entity);

        void removeEntity(std::shared_ptr<EntityNS::Entity> entity);

        World(const std::string& image);

        World();

        const std::vector<std::shared_ptr<EntityNS::Entity>>& getEntities() const;

        std::shared_ptr<EntityNS::Entity> getPlayer() const;

        std::string getType() const final;

        void onNotify(std::shared_ptr<EntityNS::Entity> entity, Utils::Event event) final;
    };

}

#endif //PROJECT_SPACE_INVADERS_WORLD_H
