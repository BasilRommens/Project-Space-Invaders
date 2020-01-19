/**
 * @file World.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the World class
 */

#ifndef PROJECT_SPACE_INVADERS_WORLD_H
#define PROJECT_SPACE_INVADERS_WORLD_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "../Exception/entity_underflow.h"
#include "Bullet.h"
#include "Entity.h"

namespace Model {

// TODO add window sizes to the world
/**
 * @brief The class that describes the world in the game
 */
class World : public Model::Entity
{
private:
        std::vector<std::shared_ptr<Model::Entity>> entities; ///< All the entities of the game itself

        double endLine{0.f}; ///< The variable that keeps the end of the world

        bool end{false}; ///< indicates if this world has ended

        /**
         * @brief checks if two already collidable entities are colliding
         * @param thisEntity: The first entity to check
         * @param otherEntity: The second entity to check
         * @return if the two entities do indeed collide
         */
        bool areColliding(std::shared_ptr<Entity> thisEntity, std::shared_ptr<Entity> otherEntity) const;

        /**
         * @brief This member function chooses what to do with 2 colliding entities
         * @param thisEntity: The entity that needs to be checked
         * @param otherEntity: The other entity that needs to be checked
         */
        void handleColliding(std::shared_ptr<Entity> thisEntity, std::shared_ptr<Entity> otherEntity);

        /**
         * @brief checks if the entity can fire a bullet
         * @param entity: The entity to be checked if it can fire a bullet
         * @return True if it can fire a vullet
         */
        bool canFire(std::shared_ptr<Model::Entity> entity) const;

        /**
         * @brief Will check all the objects in the world to check for collisions and handle them if there are
         * @param pairs: All The collision pairs that already have been checked
         * @return If the pairs vector didnt grow
         */
        bool checkCollisions(std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>& pairs);

        /**
         * @brief checks if the two entities can collide with one another
         * @param thisEntity: The first entity
         * @param otherEntity: The other entity
         * @param pairs: All the collision pairs
         * @return if they can collide
         */
        bool validCollisionPair(std::shared_ptr<Model::Entity> thisEntity, std::shared_ptr<Model::Entity> otherEntity,
                                std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>& pairs);

        /**
         * @brief will determine if the pair already does exist in the pairs vector
         * @param pairs: The vector in which to check
         * @param thisEntity: First entity
         * @param otherEntity: Second entity
         * @return True if it is in the pairs
         */
        bool inPairs(std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>>& pairs,
                     std::shared_ptr<Model::Entity> thisEntity, std::shared_ptr<Model::Entity> otherEntity);

        /**
         * @brief determines which of the 2 entities is the bullet
         * @param thisEntity: The first entity
         * @param otherEntity: The second entity
         * @return a pair of a bullet (always first) and entity (always second) can be both bullets
         */
        std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>> determineBulletEntity(
            std::shared_ptr<Model::Entity> thisEntity, std::shared_ptr<Model::Entity> otherEntity);

public:
        /**
         * @brief The destructor of an object of the world class
         */
        ~World() final;

        /**
         * @brief adds an entity to the world class
         * @param entity: The entity that will be part of the world class
         */
        void addEntity(std::shared_ptr<Model::Entity> entity);

        /**
         * @brief The constructor of a world object uses an image which it converts to a texture to use later in the
         * game
         * @param image: The image to use
         * @param endLine: The end of the world, when passed the game will end
         */
        World(const std::string& image, double endLine);

        /**
         * @brief The default constructor of the world
         */
        World() = default;

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
         * @throws Exception::entity_underflow when we want to shoot a bullet from an entity and it just has been shot
         * down
         */
        void onNotify(std::shared_ptr<Model::Entity> entity, Utils::Event event) final;

        /**
         * @brief fires the bullet from a certain entity, and adds it to the world
         * @param entity: The entity from which the bullet needs to be fired
         * @throws std::invalid_argument If the entity is not of the ship type then it cant fire a bullet
         */
        void fireBullet(std::shared_ptr<Model::Entity> entity);

        /**
         * @return if the world still contains a playership
         */
        bool hasPlayer() const;

        /**
         * @return if the world has no enemies left then go to the next level
         */
        bool hasEnemies() const;

        /**
         * @brief checks if there is at least one of the entities in the game
         * @param entityType: The type that needs to be checked
         * @return True if the entity is present in the world
         */
        bool hasEntity(const std::string& entityType) const;

        /**
         * @brief will reset the world, i.e. removing all the entities from itself and removing all the observers
         */
        void reset();

        /**
         * @param entity: The entity that we need to check for if it has crossed the endline
         * @return if the entity has crossed the endLine
         */
        bool hitEndLine(std::shared_ptr<Model::Entity> entity);

        /**
         * @return If the world has ended
         */
        bool isEnd() const;

        /**
         * @brief Sets the new end state of the world
         * @param localEnd: The variable that will set the end of the world
         */
        void setEnd(bool localEnd);
};

} // namespace Model

#endif // PROJECT_SPACE_INVADERS_WORLD_H
