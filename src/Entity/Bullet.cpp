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
    this->pos.moveYPos(directionSpeed);

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
