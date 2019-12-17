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
#include "json.hpp"
#include "Controller.h"
#include "Entity/World.h"

using nlohmann::json;

class Game {
private:
    World world;

    /**
     * @brief loads a level from a json file
     * @param level: The filename of the level to be loaded
     */
    void load(const std::string& level);

    void loadPlayer(const std::string& player);

    void loadEnemy(const std::string& enemy);

public:
    Game(const std::string& world);

    /**
     * @brief Starts playing levels in the order they are passed through
     * @param levels: The levels that will be played in order when succesfully completed
     */
    void start(std::vector<std::string> levels);

    /**
     * @brief Plays the level currently loaded in the model
     * @return If the level was succesfully finished
     */
    bool play();
};

#endif //PROJECT_SPACE_INVADERS_GAME_H
