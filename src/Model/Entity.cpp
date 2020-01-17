/**
 * @file Entity.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the class Entity
 */

#include "Entity.h"

Model::Entity::Entity(const std::string& image) : image(image) { texture.loadFromFile(image); }

void Model::Entity::onNotify(std::shared_ptr<Entity> entity, Utils::Event event) {}

std::string Model::Entity::getType() const { return std::string(); }

const sf::Texture& Model::Entity::getTexture() const { return texture; }

const std::string& Model::Entity::getImage() const { return image; }

double Model::Entity::getDamage() const { return 0; }

bool Model::Entity::isInControl() const { return false; }

void Model::Entity::setInControl()
{
        // Do nothing
}

std::shared_ptr<Utils::Position> Model::Entity::getPos() const
{
        return std::make_shared<Utils::Position>(Utils::Position(0, 0));
}

void Model::Entity::setPosition(Utils::Position newPos) {}

std::weak_ptr<Model::Entity> Model::Entity::getFrom() const { return std::weak_ptr<Entity>(); }

double Model::Entity::getDistance() const { return 0; }

const Utils::Hitbox& Model::Entity::getHitbox() const { return *(new Utils::Hitbox(0, 0)); }

void Model::Entity::addBullet(std::shared_ptr<Bullet> dummyBullet) {}

std::shared_ptr<Model::Entity> Model::Entity::spawnBullet() const { return nullptr; }

std::shared_ptr<Model::Bullet> Model::Entity::getDummyBullet() const { return nullptr; }

void Model::Entity::doDamage(double damage) {}

bool Model::Entity::collidable() const { return false; }

double Model::Entity::getHealth() const { return 0; }

int Model::Entity::getCurrentDelay() const { return 0; }

void Model::Entity::removeThis() {}

Utils::Direction Model::Entity::getDirection() const { return Utils::Direction::UP; }