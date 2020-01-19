/**
 * @file World.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the World class
 */

#include "World.h"
#include "../utils/Collision.h"

void Model::World::addEntity(std::shared_ptr<Entity> entity)
{
        try {
                Utils::Collision collision{};
                // If the entity doesnt point to anything then dont add it to the file
                if (!entity) {
                        std::cerr
                            << "No observer has been passed through in the method addObserver from the class Subject"
                            << std::endl;
                        return;
                } // If the entity type is a bullet then quit the procedure to check for collisions
                else if (entity->getType() != "bullet") {
                        // here we are going to check if all the element to insert isnt going to collide with the other
                        // elements otherwise we cant add it
                        for (std::shared_ptr<Entity> worldEntity : entities) {
                                // If the entity to be added is colliding with an entity of the world then quit the
                                // function and display error message
                                if (collision.areColliding(worldEntity, entity)) {
                                        std::cerr << "The current to be inserted entity is colliding with the entities "
                                                     "already "
                                                     "in the world, therefore it won't be added"
                                                  << std::endl;
                                        return;
                                }
                        }
                }
                // add the entity to the entities
                entities.push_back(entity);
        } catch (const std::exception& e) {
                std::cout << e.what() << std::endl;
                std::cout
                    << "Model::World::addEntity(std::shared_ptr<Entity> entity): No entity has been added to the world"
                    << std::endl;
        }
}

Model::World::World(const std::string& image, double endLine) : Entity(image), endLine(endLine) {}

const std::vector<std::shared_ptr<Model::Entity>>& Model::World::getEntities() const { return entities; }

std::shared_ptr<Model::Entity> Model::World::getPlayer() const
{
        for (auto entity : entities) {
                std::string type = entity->getType();
                if (type == "player") {
                        return entity;
                }
        }
        return nullptr;
}

std::string Model::World::getType() const { return "world"; }

void Model::World::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
        Utils::Collision collision{};
        if (event == Utils::Event::CHECK_COLLISIONS) {
                std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<Model::Entity>> doubleBreak;
                std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> pairs;
                do {
                        doubleBreak = collision.checkCollisions(pairs, entities);
                        // If a pair has been found then it wont be a nullpointer
                        if (doubleBreak.first) {
                                handleColliding(doubleBreak.first, doubleBreak.second);
                        }
                } while (doubleBreak.first);
        } else if (entity and event == Utils::Event::MOVED_DOWN) {
                // TODO Fix this code because it will error big time
        }

        if (not entity and event == Utils::Event::FIRE_BULLET) {
                throw Exception::entity_underflow("There is no entity to fire the bullet from");
        }
}

Model::World::~World() { entities.clear(); }

void Model::World::fireBullet(std::shared_ptr<Model::Entity> entity)
{
        if (not canFire(entity)) {
                throw std::invalid_argument("The type of the entity isnt of the ship type");
        } else if (canFire(entity) and not entity->getCurrentDelay()) {
                // Create a bullet with that needs to depart from the certain ship
                std::shared_ptr<Entity> bullet = entity->spawnBullet();
                this->addEntity(bullet);
                notify(bullet, Utils::Event::NEW_DRAW);
        }
}

bool Model::World::hasPlayer() const { return hasEntity("player"); }

void Model::World::reset()
{
        entities.clear();
        this->clearObservers();
}

bool Model::World::hasEnemies() const { return hasEntity("enemy"); }

bool Model::World::hitEndLine(std::shared_ptr<Model::Entity> entity) { return entity->getPos()->getY() < endLine; }

bool Model::World::isEnd() const { return end; }

void Model::World::setEnd(bool localEnd) { World::end = localEnd; }

bool Model::World::hasEntity(const std::string& entityType) const
{
        for (std::shared_ptr<Entity> entity : entities) {
                // If we found an enemy in the world then return true
                if (entity->getType() == entityType) {
                        return true;
                }
        }
        // If we didnt find an enemy then return false
        return false;
}

bool Model::World::canFire(std::shared_ptr<Model::Entity> entity) const
{
        return entity->getType() == "player" or entity->getType() == "enemy";
}

void Model::World::handleColliding(std::shared_ptr<Model::Entity> thisEntity,
                                   std::shared_ptr<Model::Entity> otherEntity)
{
        // If we find that both the entities are not bullets then delete both the entities
        // if both are bullets then delete them too
        if ((thisEntity->getType() != "bullet" and otherEntity->getType() != "bullet") or
            (thisEntity->getType() == "bullet" and otherEntity->getType() == "bullet")) {
                // Delete the second entity from the world
                entities.erase(std::find(entities.begin(), entities.end(), thisEntity));
                notify(thisEntity, Utils::Event::REMOVE); // Notify that there are entities to be removed
                removeObserver(thisEntity);
                // Delete the second entity from the world
                entities.erase(std::find(entities.begin(), entities.end(), otherEntity));
                notify(otherEntity, Utils::Event::REMOVE); // Notify that there are entities to be removed
                removeObserver(otherEntity);
                // They wont be updated anymore but still drawn every iteration on the same spot
                return;
        }
        // Decide which of the two entities is the bullet and then put it in a dedicated bullet variable
        std::shared_ptr<Model::Entity> bullet = ((thisEntity->getType() == "bullet") ? thisEntity : otherEntity);
        // Take the other as the entity that is hit by the bullet
        std::shared_ptr<Model::Entity> entity = ((thisEntity->getType() == "bullet") ? otherEntity : thisEntity);

        // If the bullet can travel through then no collisions are happening
        Utils::Collision collision{};
        if (collision.canTravelThrough(bullet->getDirection(), entity->getType())) {
                return;
        }

        entity->doDamage(bullet->getDamage());

        // Delete the bullet from the world because it can not do damage anymore
        entities.erase(std::find(entities.begin(), entities.end(), bullet));
        notify(bullet, Utils::Event::REMOVE); // Notify that there are entities to be removed
        // Delete the entity from the world if it has no health more left
        if (entity->getHealth() <= 0) {
                entities.erase(std::find(entities.begin(), entities.end(), entity));
                notify(entity, Utils::Event::REMOVE); // Notify that there are entities to be removed
                removeObserver(entity);
        }
}
