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
#include "Bullet.h"

namespace EntityNS {

    class Ship : public Entity {
    protected:
        Utils::Position pos;
        double health;
        double HSpeed;
        // TODO make the bullet delay in the input files
        const int bulletDelay{30};
        int currentDelay;
        Hitbox hitbox;
        std::shared_ptr<Bullet> dummyBullet;

        virtual void moveRight() = 0;

        virtual void moveLeft() = 0;

        virtual void fireBullet() = 0;

        void resetDelay();

        void decreaseDelay();

    public:
        virtual ~Ship();

        Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
                int bulletDelay, const Hitbox& hitbox);

        std::string getType() const override;

        std::shared_ptr<Utils::Position> getPos() const final;

        void setPosition(Utils::Position newPos) final;

        double getDamage() const final;

        const Hitbox& getHitbox() const final;

        void addBullet(std::shared_ptr<Bullet> dummyBullet) final;

        std::shared_ptr<EntityNS::Entity> spawnBullet() final;

        std::shared_ptr<Bullet> getDummyBullet() const final;

        void doDamage(double damage) final;

        bool collidable() const final;

        double getHealth() const;

        int getCurrentDelay() const final;
    };

}

#endif //PROJECT_SPACE_INVADERS_SHIP_H
