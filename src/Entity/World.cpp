/**
 * @file World.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the World class
 */

#include "World.h"

void EntityNS::World::addEntity(std::shared_ptr<Entity> entity)
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

void EntityNS::World::removeEntity(std::shared_ptr<Entity> entity)
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

EntityNS::World::World(const std::string& image)
        :Entity(image) { }

EntityNS::World::World() { }

const std::vector<std::shared_ptr<EntityNS::Entity>>& EntityNS::World::getEntities() const
{
    return entities;
}

std::shared_ptr<EntityNS::Entity> EntityNS::World::getPlayer() const
{
    for (auto entity: entities) {
        std::string type = entity->getType();
        if (type=="player") {
            return entity;
        }
    }
    return nullptr;
}

std::string EntityNS::World::getType() const
{
    return "world";
}

void EntityNS::World::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    // TODO clean up this function
    if (event==Utils::Event::CHECK_COLLISIONS) {
        std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> pairs;
        // Check for every entity except itself if it intersects with one
        for (auto thisEntity: entities) {
            for (auto otherEntity: entities) {
                // TODO why is it behaving so weird
                if (not thisEntity or not otherEntity) {
                    continue;
                }
                if (thisEntity==otherEntity) {
                    continue;
                }
                // TODO simplify this with a std algorithm function
                auto foundPair = false;
                for (const auto& pair: pairs) {
                    if ((pair.first==thisEntity and pair.second==otherEntity)
                            or (pair.first==otherEntity and pair.second==thisEntity)) {
                        foundPair = true;
                        break;
                    }
                }
                // If we have found the pair then continue without further performing anything
                // or we found that one of the entities is not able to collide
                if (foundPair or not thisEntity->collidable() or not otherEntity->collidable()) {
                    continue;
                } // If the pair is not found in the collections of pairs then add it
                else {
                    pairs.emplace_back(std::make_pair(thisEntity, otherEntity));
                }

                // TODO add extra checks for bullets passing enemy ships when the bullet is enemy
                std::shared_ptr<Entity> bullet;
                std::shared_ptr<Entity> entity;
                // Trying to identify the bullet entity
                if (thisEntity->getType()=="bullet") {
                    bullet = thisEntity;
                    entity = otherEntity;
                }
                else {
                    bullet = otherEntity;
                    entity = thisEntity;
                }

                // If we haven't found it then we can check if the two objects collide with one another
                if (areColliding(thisEntity, otherEntity) and bullet->getFrom().lock().get()!=entity.get()) {
                    handleColliding(thisEntity, otherEntity);
                }
            }
        }
    }

    // TODO throw error when no entity is detected
    if (not entity and event==Utils::Event::FIRE_BULLET) {
        throw std::domain_error("There is no entity to fire the bullet from");
    }
    if (event==Utils::Event::FIRE_BULLET and entity) {
        // Ensure that the type that is firing the bullet is of the ship type (dynamic casting to check doesnt work)
        // and have it so that there still needs to be a delay present between firing the bullets the current delay cant be more than 0
        if ((entity->getType()=="player" or entity->getType()=="enemy") and not entity->getCurrentDelay()) {
            // Create a bullet with that needs to depart from the certain ship
            std::shared_ptr<Entity> bullet = entity->spawnBullet();
            this->addEntity(bullet);
            notify(bullet, Utils::Event::NEW_DRAW);
        }
    }
}

EntityNS::World::~World()
{
    entities.clear();
}

bool EntityNS::World::areColliding(const std::shared_ptr<Entity> thisEntity, const std::shared_ptr<Entity> otherEntity)
{
    return thisEntity->getPos()->getX()<otherEntity->getPos()->getX()+otherEntity->getHitbox().getWidth()
            and thisEntity->getPos()->getX()+thisEntity->getHitbox().getWidth()>otherEntity->getPos()->getX()
            and thisEntity->getPos()->getY()<otherEntity->getPos()->getY()+otherEntity->getHitbox().getHeight()
            and thisEntity->getPos()->getY()+thisEntity->getHitbox().getHeight()>otherEntity->getPos()->getY();
}

void EntityNS::World::handleColliding(std::shared_ptr<Entity> thisEntity, std::shared_ptr<Entity> otherEntity)
{
    // If we find that both the entities are not bullets then delete both the entities
    // if both are bullets then delete them too
    if ((thisEntity->getType()!="bullet" and otherEntity->getType()!="bullet")
            or (thisEntity->getType()=="bullet" and otherEntity->getType()=="bullet")) {
        // Delete the second entity from the world
        entities.erase(std::find(entities.begin(), entities.end(), thisEntity));
        notify(thisEntity, Utils::Event::REMOVE); // Notify that there are entities to be removed
        // Delete the second entity from the world
        entities.erase(std::find(entities.begin(), entities.end(), otherEntity));
        notify(otherEntity, Utils::Event::REMOVE); // Notify that there are entities to be removed
        // They wont be updated anymore but still drawn every iteration on the same spot
        return;
    }
    // Decide which of the two entities is the bullet and then put it in a dedicated bullet variable
    std::shared_ptr<Entity> bullet = ((thisEntity->getType()=="bullet") ? thisEntity : otherEntity);
    // Take the other as the entity that is hit by the bullet
    std::shared_ptr<Entity> entity = ((thisEntity->getType()=="bullet") ? otherEntity : thisEntity);

    // TODO maybe improve the name of the function
    entity->doDamage(bullet->getDamage());

    // Delete the bullet from the world because it can not do damage anymore
    entities.erase(std::find(entities.begin(), entities.end(), bullet));
    notify(bullet, Utils::Event::REMOVE); // Notify that there are entities to be removed
    // Delete the entity from the world if it has no health more left
    if (entity->getHealth()<=0) {
        entities.erase(std::find(entities.begin(), entities.end(), entity));
        notify(entity, Utils::Event::REMOVE); // Notify that there are entities to be removed
    }
}
