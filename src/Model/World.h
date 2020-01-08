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

namespace Model {

// TODO add window sizes to the world
    /**
     * @brief The class that describes the world in the game
     */
    class World : public Model::Entity {
    private:
        std::vector<std::shared_ptr<Model::Entity>> entities; ///< All the entities of the game itself

        double endLine{0.f};

        /**
         * @brief checks if two already collidable entities are colliding
         * @param thisEntity: The first entity to check
         * @param otherEntity: The second entity to check
         * @return if the two entities do indeed collide
         * TODO check if the two entities can collide indeed
         */
        bool areColliding(std::shared_ptr<Entity> thisEntity, std::shared_ptr<Entity> otherEntity) const;

        /**
         * @brief This member function chooses what to do with 2 colliding entities
         * @param thisEntity: The entity that needs to be checked
         * @param otherEntity: The other entity that needs to be checked
         * TODO check if they are indeed colliding
         */
        void handleColliding(std::shared_ptr<Entity> thisEntity, std::shared_ptr<Entity> otherEntity);

    public:
        /**
         * @brief The destructor of an object of the world class
         */
        virtual ~World();

        /**
         * @brief adds an entity to the world class
         * @param entity: The entity that will be part of the world class
         */
        void addEntity(std::shared_ptr<Model::Entity> entity);

        /**
         * @brief removes an entity to the world class
         * @param entity: The entity that will be removed from the world class
         */
        void removeEntity(std::shared_ptr<Model::Entity> entity);

        /**
         * @brief The constructor of a world object uses an image which it converts to a texture to use later in the game
         * @param image: The image to use
         * TODO check if the image is usable
         */
        World(const std::string& image, double endLine);

        /**
         * @brief The default constructor of the world
         */
        World();

        /**
         * @return The entities of the world
         */
        const std::vector<std::shared_ptr<Model::Entity>>& getEntities() const;

        /**
         * @return The player ship that is in the entities
         */
        std::shared_ptr<Model::Entity> getPlayer() const;

        /**
         * @return The type of the entity ("world")
         */
        std::string getType() const final;

        /**
         * @brief Reacts upon a notification from all the subjects that have this object as an observer in their classes
         * @param entity: The entity that can be used in the notification
         * @param event: The event that has made this notification possible
         */
        void onNotify(std::shared_ptr<Model::Entity> entity, Utils::Event event) final;

        /**
         * @brief fires the bullet from a certain entity, and adds it to the world
         * @param entity: The entity from which the bullet needs to be fired
         */
        void fireBullet(std::shared_ptr<Model::Entity> entity);
    };

}

#endif //PROJECT_SPACE_INVADERS_WORLD_H
