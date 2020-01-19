/**
 * @file Collision.h
 * @author Basil Rommens
 * @date 1/19/20
 * @brief The header file of the class Collision
 */

#ifndef PROJECT_SPACE_INVADERS_COLLISION_H
#define PROJECT_SPACE_INVADERS_COLLISION_H

#include "Model/Entity.h"

/**
 * @addtogroup Utils
 * @{
 */
namespace Utils {

    /**
     * We use this class to make using collision detection easier
     */
class Collision
{
private:
        /**
         * @brief checks if the two entities can collide with one another
         * @param thisEntity: The first entity
         * @param otherEntity: The other entity
         * @param pairs: All the collision pairs
         * @return if they can collide
         */
        bool validCollisionPair(
            std::shared_ptr<Model::Entity> thisEntity, std::shared_ptr<Model::Entity> otherEntity,
            std::vector<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>>>& pairs);

        /**
         * @brief will determine if the pair already does exist in the pairs vector
         * @param pairs: The vector in which to check
         * @param thisEntity: First entity
         * @param otherEntity: Second entity
         * @return True if it is in the pairs
         */
        bool inPairs(std::vector<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>>>& pairs,
                     std::shared_ptr<Model::Entity> thisEntity, std::shared_ptr<Model::Entity> otherEntity);

        /**
         * @brief determines which of the 2 entities is the bullet
         * @param thisEntity: The first entity
         * @param otherEntity: The second entity
         * @return a pair of a bullet (always first) and entity (always second) can be both bullets
         */
        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>> determineBulletEntity(
            std::shared_ptr<Model::Entity> thisEntity, std::shared_ptr<Model::Entity> otherEntity);

public:
        Collision() = default;

        /**
         * @brief checks if two already collidable entities are colliding
         * @param thisEntity: The first entity to check
         * @param otherEntity: The second entity to check
         * @return true if the two entities do indeed collide
         */
        bool areColliding(std::shared_ptr<Model::Entity> thisEntity, std::shared_ptr<Model::Entity> otherEntity) const;

        /**
         * @brief checks if a bullet can travel through an entity
         * @param direction: Direction of the bullet
         * @param typeEntity: The type of the entity
         * @return if it can travel through an entity
         */
        bool canTravelThrough(Utils::Direction direction, const std::string& typeEntity);

        /**
         * @brief Will check all the objects in the world to check for collisions and handle them if there are
         * @param pairs: All The collision pairs that already have been checked
         * @param entities: All the entities that are in the world
         * @return If the pairs vector didnt grow and the pair that collides
         */
        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>> checkCollisions(
            std::vector<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>>>& pairs,
            const std::vector<std::shared_ptr<Model::Entity>>& entities);
};

} // namespace Utils
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_COLLISION_H
