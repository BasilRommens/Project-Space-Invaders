/**
 * @file Bullet.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the class Bullet
 */

#include "Bullet.h"

Model::Bullet::Bullet(const std::string& image, Utils::Direction direction, double speed, double damage,
        const Utils::Position& pos, std::weak_ptr<Entity> from, Utils::Hitbox hitbox)
        :Entity(image), direction(direction), speed(speed), damage(damage), pos(pos), from(from), hitbox(hitbox)
{
    texture.loadFromFile(image);
}

std::string Model::Bullet::getType() const
{
    return "bullet";
}

std::shared_ptr<Utils::Position> Model::Bullet::getPos() const
{
    return std::make_shared<Utils::Position>(pos);
}

std::weak_ptr<Model::Entity> Model::Bullet::getFrom() const
{
    return from;
}

bool Model::Bullet::isInControl() const
{
    return inControl;
}

void Model::Bullet::setInControl()
{
    Bullet::inControl = true;
}

void Model::Bullet::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    // check that the bullet to update equals the bullet that is being called
    if (shared_from_this().get()!=entity.get()) {
        return;
    }
    // In case that the events dont match return too
    if (event!=Utils::Event::UPDATE_DRAW) {
        return;
    }

    // update the bullets position
    // Decide the direction of the bullet
    double directionSpeed;
    if (direction==Utils::Direction::DOWN) {
        directionSpeed = -speed;
    }
    else {
        directionSpeed = speed;
    }
    try {
        this->pos.moveYPos(directionSpeed, hitbox);
    }
    catch (std::exception& test) { // TODO improve the name of the variable
        notify(shared_from_this(), Utils::Event::REMOVE);
        return;
    }

    // notify that there needs to be a sprite move of the current bullet
    notify(shared_from_this(), Utils::Event::UPDATE_DRAW);
}

void Model::Bullet::setPosition(Utils::Position newPos)
{
    pos.setPosition(newPos);
}

Model::Bullet::~Bullet()
{

}

Model::Bullet::Bullet(std::shared_ptr<Bullet> other)
{
    this->direction = other->direction;
    this->hitbox = other->hitbox;
    this->speed = other->speed;
    this->pos = other->pos; // Needs modification later on
    this->damage = other->damage;
    this->from = other->from;
    this->inControl = other->inControl;
    this->image = other->image;
    this->texture = other->texture;
    this->addObserver(other->retrieveObserver("world"));

    // Move the position of the dummy bullet such that it is in the correct position relative to the entity that is firing it
    this->pos.moveXPos(other->from.lock()->getPos()->getX(), hitbox);
    this->pos.moveYPos(other->from.lock()->getPos()->getY(), hitbox);
}

bool Model::Bullet::collidable() const
{
    return true;
}

double Model::Bullet::getDamage() const
{
    return damage;
}
