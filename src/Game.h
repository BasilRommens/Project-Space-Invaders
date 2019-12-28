/**
 * @file Game.h
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The header file of the class Game
 */

#ifndef PROJECT_SPACE_INVADERS_GAME_H
#define PROJECT_SPACE_INVADERS_GAME_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <SFML/Graphics.hpp>

#include "Entity/PlayerShip.h"
#include "Entity/EnemyShip.h"
#include "Entity/Bullet.h"
#include "Entity/World.h"
#include "utils/Stopwatch.h"
#include "utils/json.hpp"
#include "Controller.h"
#include "Draw.h"
#include "AI.h"

using json = nlohmann::json;

class Game {
private:
    AI ai;

    EntityNS::World world;

    Controller controller;

    std::shared_ptr<Utils::Stopwatch> stopwatch = stopwatch->getStopwatch();

    /**
     * @brief loads a level from a json file
     * @param level: The filename of the level to be loaded
     */
    void load(const std::string& level);

    /**
     * @brief Loads the player from a string given with it
     * @param player: The filename which to parse
     */
    void loadPlayer(const std::string&& player);

    /**
     * @brief Loads the enemy from a string given to it
     * @param enemy: The filename which to parse
     */
    void loadEnemy(const std::string&& enemy);

    /**
     * @brief Loads the world from a string given to it
     * @param worldName: The filename of the graphical representation of the world
     */
    void loadWorld(const std::string&& worldName);

    /**
     * @brief Plays the level currently loaded in the model
     * @param renderWindow: The window which shows the game that needs to run
     * @return If the level was succesfully finished
     */
    bool play(sf::RenderWindow& renderWindow);

    void wait();

    std::shared_ptr<EntityNS::Bullet> createBullet(std::string fileName);

public:

    /**
     * @brief The default game constructor
     */
    Game();

    /**
     * @brief Starts playing levels in the order they are passed through
     * @param levels: The levels that will be played in order when succesfully completed
     */
    void start(std::vector<std::string> levels);
};

#endif //PROJECT_SPACE_INVADERS_GAME_H
