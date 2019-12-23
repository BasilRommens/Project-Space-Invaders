/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
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

        void fireBullet();

    public:
        virtual ~PlayerShip();

        PlayerShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double damage);

        std::string getType() const override;
    };

}

#endif //PROJECT_SPACE_INVADERS_PLAYERSHIP_H
