/**
 * @file PlayerShip.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the class PlayerShip
 */

#ifndef PROJECT_SPACE_INVADERS_PLAYERSHIP_H
#define PROJECT_SPACE_INVADERS_PLAYERSHIP_H

#include "Ship.h"

namespace EntityNS {

    class PlayerShip : public Ship {
    private:
        virtual void onNotify(std::shared_ptr<Entity> entity, Utils::Event event);

        void moveRight();

        void moveLeft();

        void fireBullet() override;

    public:
        virtual ~PlayerShip();

        PlayerShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double damage,
                int bulletDelay, const Hitbox& hitbox, std::shared_ptr<Bullet> dummyBullet);

        std::string getType() const override;
    };

}

#endif //PROJECT_SPACE_INVADERS_PLAYERSHIP_H
