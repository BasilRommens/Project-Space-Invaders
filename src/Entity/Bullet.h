/**
 * @file Bullet.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the Bullet class
 */

#ifndef PROJECT_SPACE_INVADERS_BULLET_H
#define PROJECT_SPACE_INVADERS_BULLET_H

#include "Entity.h"
#include "../utils/Position.h"
#include "Ship.h"

class Bullet : public Entity {
private:
    Utils::Direction direction;
    double speed;
    double damage;
    Utils::Position pos;
    std::shared_ptr<Entity> from;
public:
    Bullet(const std::string& image, Utils::Direction direction, double speed, double damage,
            const Utils::Position& pos, std::shared_ptr<Entity> from);

    std::string getType() const override;

    Utils::Position getPos() const override;

    std::shared_ptr<Entity> getFrom() const final;
};

#endif //PROJECT_SPACE_INVADERS_BULLET_H
