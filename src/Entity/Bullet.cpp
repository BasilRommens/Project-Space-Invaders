/**
 * @file Bullet.cpp
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The cpp file of the class Bullet
 */

#include "Bullet.h"

Bullet::Bullet(const std::string& image, Utils::Direction direction, double speed, double damage,
        const Utils::Position& pos, std::shared_ptr<Entity> from)
        :Entity(image), direction(direction), speed(speed), damage(damage), pos(pos), from(from)
{
    texture.loadFromFile(image);
}

std::string Bullet::getType() const
{
    return "bullet";
}

Utils::Position Bullet::getPos() const
{
    return pos;
}

std::shared_ptr<Entity> Bullet::getFrom() const
{
    return from;
}

bool Bullet::isInControl() const
{
    return inControl;
}

void Bullet::setInControl()
{
    Bullet::inControl = true;
}

void Bullet::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    // check that the bullet to update equals the bullet that is being called
    if (shared_from_this().get()!=entity.get()) {
        return;
    }
    std::cout << "successful entrance" << std::endl;

    // update the bullets position
    // Decide the direction of the bullet
    double directionSpeed;
    if (direction==Utils::Direction::DOWN) {
        directionSpeed = speed;
    }
    else {
        directionSpeed = -speed;
    }
    this->pos.moveYPos(directionSpeed);

    // notify that there needs to be a sprite move of the current bullet
    notify(shared_from_this(), Utils::Event::UPDATE_DRAW);
}
