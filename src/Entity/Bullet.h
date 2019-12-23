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
    bool inControl{false};
public:
    Bullet(const std::string& image, Utils::Direction direction, double speed, double damage,
            const Utils::Position& pos, std::shared_ptr<Entity> from);

    std::string getType() const override;

    std::shared_ptr<Utils::Position> getPos() const final;

    void setPosition(Utils::Position newPos) final;

    std::shared_ptr<Entity> getFrom() const final;

    bool isInControl() const final;

    void setInControl() final;

    void onNotify(std::shared_ptr<Entity> entity, Utils::Event event) override;
};

#endif //PROJECT_SPACE_INVADERS_BULLET_H
