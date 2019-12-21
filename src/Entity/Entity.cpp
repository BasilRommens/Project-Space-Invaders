/**
 * @file Entity.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the class Entity
 */

#include "Entity.h"

Entity::Entity(const std::string& image)
        :image(image)
{
    texture.loadFromFile(image);
}

Entity::Entity() { }

void Entity::onNotify(std::shared_ptr<Entity> entity, Utils::Event event) { }

std::string Entity::getType() const
{
    return std::string();
}

Utils::Position Entity::getPos() const
{
    return Utils::Position{};
}

const sf::Texture& Entity::getTexture() const
{
    return texture;
}

const std::string& Entity::getImage() const
{
    return image;
}
