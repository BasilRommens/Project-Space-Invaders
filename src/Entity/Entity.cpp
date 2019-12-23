/**
 * @file Entity.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the class Entity
 */

#include "Entity.h"

EntityNS::Entity::Entity(const std::string& image)
        :image(image)
{
    texture.loadFromFile(image);
}

EntityNS::Entity::Entity() { }

void EntityNS::Entity::onNotify(std::shared_ptr<Entity> entity, Utils::Event event) { }

std::string EntityNS::Entity::getType() const
{
    return std::string();
}

const sf::Texture& EntityNS::Entity::getTexture() const
{
    return texture;
}

const std::string& EntityNS::Entity::getImage() const
{
    return image;
}

double EntityNS::Entity::getDamage() const
{
    return 0;
}

std::shared_ptr<Observer> EntityNS::Entity::getDrawShared()
{
    for (auto observer: this->getObservers()) {
        if (observer->getType()=="draw") {
            return observer;
        }
    }
    return nullptr;
}

std::shared_ptr<EntityNS::Entity> EntityNS::Entity::getFrom() const
{
    return nullptr;
}

bool EntityNS::Entity::isInControl() const
{
    return false;
}

void EntityNS::Entity::setInControl()
{
    // Do nothing
}

std::shared_ptr<Utils::Position> EntityNS::Entity::getPos() const
{
    return std::shared_ptr<Utils::Position>();
}

void EntityNS::Entity::setPosition(Utils::Position newPos)
{

}

EntityNS::Entity::~Entity()
{

}
