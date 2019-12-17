/**
 * @file 
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_GAME_H
#define PROJECT_SPACE_INVADERS_GAME_H

#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Entity/PlayerShip.h"
#include "Entity/EnemyShip.h"
#include "Entity/Bullet.h"
#include "Entity/"

class Game {
private:
    void load(std::string level);

public:
    void start(std::vector<std::string> levels);

    bool play();
};

#endif //PROJECT_SPACE_INVADERS_GAME_H
