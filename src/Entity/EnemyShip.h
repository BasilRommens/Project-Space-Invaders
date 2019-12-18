/**
 * @file EnemyShip.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the class EnemyShip
 */

#ifndef PROJECT_SPACE_INVADERS_ENEMYSHIP_H
#define PROJECT_SPACE_INVADERS_ENEMYSHIP_H

#include "Ship.h"

class EnemyShip : public Ship {
private:
    double VSpeed;

    virtual void onNotify(Utils::Event event);

    void moveRight();

    void moveLeft();

    void fireBullet();

public:
    EnemyShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double damage,
            double vSpeed);
};

#endif //PROJECT_SPACE_INVADERS_ENEMYSHIP_H
