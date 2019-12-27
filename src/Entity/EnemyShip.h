/**
 * @file EnemyShip.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the class EnemyShip
 */

#ifndef PROJECT_SPACE_INVADERS_ENEMYSHIP_H
#define PROJECT_SPACE_INVADERS_ENEMYSHIP_H

#include <random>

#include "Ship.h"

namespace EntityNS {

    class EnemyShip : public Ship {
    private:
        double VSpeed;

        static double distance; ///< Variable that keeps the distance travelled by the ship

        static std::vector<std::weak_ptr<EnemyShip>> otherShips;

        bool moved;

        Utils::Direction direction{Utils::Direction::LEFT}; ///< It keeps the current direction the ship is moving

        virtual void onNotify(std::shared_ptr<Entity> entity, Utils::Event event) final;

        void moveRight() final;

        void moveLeft() final;

        void fireBullet() final;

        void swapDirection(std::shared_ptr<EnemyShip> ship);

        int randomOffset();

    public:
        virtual ~EnemyShip();

        EnemyShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double damage,
                const int bulletDelay, double vSpeed);

        std::string getType() const final;

        double getDistance() const final;

        static void addShip(std::weak_ptr<EnemyShip> ship);
    };
}

#endif //PROJECT_SPACE_INVADERS_ENEMYSHIP_H
