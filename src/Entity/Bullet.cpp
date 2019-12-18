/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#include "Bullet.h"

Bullet::Bullet(const std::string& image, Utils::Direction direction, double speed, double damage,
        const Utils::Position& pos)
        :Entity(image), direction(direction), speed(speed), damage(damage), pos(pos) { }

std::string Bullet::getType() const
{
    return "bullet";
}
