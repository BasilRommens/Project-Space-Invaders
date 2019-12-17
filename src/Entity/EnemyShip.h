/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_ENEMYSHIP_H
#define PROJECT_SPACE_INVADERS_ENEMYSHIP_H

#include "Ship.h"

class EnemyShip : public Ship {
private:
    double VSpeed;
public:
    EnemyShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed, double vSpeed);
};

#endif //PROJECT_SPACE_INVADERS_ENEMYSHIP_H
