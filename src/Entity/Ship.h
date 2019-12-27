/**
 * @file Ship.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the class Ship
 */

#ifndef PROJECT_SPACE_INVADERS_SHIP_H
#define PROJECT_SPACE_INVADERS_SHIP_H

#include <iostream>
#include <memory>

#include "Entity.h"
#include "../utils/Position.h"

namespace EntityNS {

    class Ship : public Entity {
    protected:
        Utils::Position pos;
        double health;
        double HSpeed;
        double damage;
        // TODO make the bullet delay in the input files
        const int bulletDelay{30};
        int currentDelay;

        virtual void moveRight() = 0;

        virtual void moveLeft() = 0;

        virtual void fireBullet() = 0;

    public:
        virtual ~Ship();

        Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double damage,
                const int bulletDelay);

        std::string getType() const override;

        std::shared_ptr<Utils::Position> getPos() const final;

        void setPosition(Utils::Position newPos) final;

        double getDamage() const override;
    };

}

#endif //PROJECT_SPACE_INVADERS_SHIP_H
