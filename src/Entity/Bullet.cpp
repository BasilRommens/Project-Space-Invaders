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
