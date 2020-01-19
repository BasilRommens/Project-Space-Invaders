/**
 * @file Collision.cpp
 * @author Basil Rommens
 * @date 1/19/20
 * @brief The cpp file of the class Collision
 */

#include "Collision.h"

std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>> Utils::Collision::checkCollisions(
    std::vector<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>>>& pairs,
    const std::vector<std::shared_ptr<Model::Entity>>& entities)
{
        // Check for every entity except itself if it intersects with one
        for (std::shared_ptr<Model::Entity> thisEntity : entities) {
                for (std::shared_ptr<Model::Entity> otherEntity : entities) {
                        if (not validCollisionPair(thisEntity, otherEntity, pairs)) {
                                continue;
                        } // If the pair is not found in the collections of pairs then add it
                        else if (not inPairs(pairs, thisEntity, otherEntity)) {
                                pairs.emplace_back(std::make_pair(thisEntity, otherEntity));
                        }

                        // bullet, localEntity pair
                        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>> bulletEntityPair =
                            determineBulletEntity(thisEntity, otherEntity);
                        std::shared_ptr<Model::Entity> bullet = bulletEntityPair.first;
                        std::shared_ptr<Model::Entity> localEntity = bulletEntityPair.second;

                        // If we haven't found it then we can check if the two objects collide with one
                        // another
                        if (areColliding(thisEntity, otherEntity) and
                            bullet->getFrom().lock().get() != localEntity.get()) {
                                // because there are entities that are deleted
                                return std::make_pair(thisEntity, otherEntity);
                        }
                }
        }
        // nullpointer because no colliding pair has been found
        return std::make_pair(nullptr, nullptr);
}

bool Utils::Collision::validCollisionPair(
    std::shared_ptr<Model::Entity> thisEntity, std::shared_ptr<Model::Entity> otherEntity,
    std::vector<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>>>& pairs)
{
        // If we dont have the other entity
        if (not thisEntity or not otherEntity) {
                return false;
        } // If they are the same
        else if (thisEntity == otherEntity) {
                return false;
        } // If one of them is the world
        else if (thisEntity->getType() == "world" or otherEntity->getType() == "world") {
                return false;
        } // If one of the entities is not collidable
        else if (not thisEntity->collidable() or not otherEntity->collidable()) {
                return false;
        }

        return not inPairs(pairs, thisEntity, otherEntity);
}

bool Utils::Collision::inPairs(
    std::vector<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>>>& pairs,
    std::shared_ptr<Model::Entity> thisEntity, std::shared_ptr<Model::Entity> otherEntity)
{
        // search for the corresponding pair in the pairs
        for (const auto& pair : pairs) {
                // found the pair
                if ((pair.first == thisEntity and pair.second == otherEntity) or
                    (pair.first == otherEntity and pair.second == thisEntity)) {
                        return true;
                }
        }
        // Didnt find the pair
        return false;
}

std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>> Utils::Collision::determineBulletEntity(
    std::shared_ptr<Model::Entity> thisEntity, std::shared_ptr<Model::Entity> otherEntity)
{
        // Trying to identify the bullet entity
        if (thisEntity->getType() == "bullet") {
                return std::make_pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>>(
                    static_cast<std::shared_ptr<Model::Entity>&&>(thisEntity),
                    static_cast<std::shared_ptr<Model::Entity>&&>(otherEntity));
        } else {
                return std::make_pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>>(
                    static_cast<std::shared_ptr<Model::Entity>&&>(otherEntity),
                    static_cast<std::shared_ptr<Model::Entity>&&>(thisEntity));
        }
}

bool Utils::Collision::canTravelThrough(Utils::Direction direction, const std::string& typeEntity)
{
        // If we find that the bullet is travelling down and it is an enemy then do nothing
        if (direction == Utils::Direction::DOWN and typeEntity == "enemy") {
                return true;
        }
        // If we find that the bullet is travelling up and it is a player then do nothing
        return direction == Utils::Direction::UP and typeEntity == "player";
}

bool Utils::Collision::areColliding(const std::shared_ptr<Model::Entity> thisEntity,
                                    const std::shared_ptr<Model::Entity> otherEntity) const
{
        /// @see https://www.gamedevelopment.blog/collision-detection-circles-rectangles-and-polygons/ (31 december 2019
        /// 13:48)
        double topEdge1 = thisEntity->getPos()->getY();
        double rightEdge1 = thisEntity->getPos()->getX() + thisEntity->getHitbox().getWidth();
        double leftEdge1 = thisEntity->getPos()->getX();
        double bottomEdge1 = thisEntity->getPos()->getY() - thisEntity->getHitbox().getHeight();

        double topEdge2 = otherEntity->getPos()->getY();
        double rightEdge2 = otherEntity->getPos()->getX() + otherEntity->getHitbox().getWidth();
        double leftEdge2 = otherEntity->getPos()->getX();
        double bottomEdge2 = otherEntity->getPos()->getY() - otherEntity->getHitbox().getHeight();

        return leftEdge1 < rightEdge2 && rightEdge1 > leftEdge2 && bottomEdge1 < topEdge2 && topEdge1 > bottomEdge2;
}
