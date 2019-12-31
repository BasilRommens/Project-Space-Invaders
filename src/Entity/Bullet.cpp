/**
 * @file Bullet.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the class Bullet
 */

#include "Bullet.h"

EntityNS::Bullet::Bullet(const std::string& image, Utils::Direction direction, double speed, double damage,
        const Utils::Position& pos, std::weak_ptr<Entity> from, Hitbox hitbox)
        :Entity(image), direction(direction), speed(speed), damage(damage), pos(pos), from(from), hitbox(hitbox)
{
    texture.loadFromFile(image);
}

std::string EntityNS::Bullet::getType() const
{
    return "bullet";
}

std::shared_ptr<Utils::Position> EntityNS::Bullet::getPos() const
{
    return std::make_shared<Utils::Position>(pos);
}

std::weak_ptr<EntityNS::Entity> EntityNS::Bullet::getFrom() const
{
    return from;
}

bool EntityNS::Bullet::isInControl() const
{
    return inControl;
}

void EntityNS::Bullet::setInControl()
{
    Bullet::inControl = true;
}

void EntityNS::Bullet::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
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

void EntityNS::Bullet::setPosition(Utils::Position newPos)
{
    pos.setPosition(newPos);
}

EntityNS::Bullet::~Bullet()
{

}

EntityNS::Bullet::Bullet(std::shared_ptr<Bullet> other)
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

bool EntityNS::Bullet::collidable() const
{
    return true;
}
