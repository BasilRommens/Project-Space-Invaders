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

#include "Model/PlayerShip.h"
#include "Model/EnemyShip.h"
#include "Model/Bullet.h"
#include "Model/World.h"
#include "utils/Stopwatch.h"
#include "utils/json.hpp"
#include "Control/Controller.h"
#include "View/Draw.h"

using json = nlohmann::json;

/**
 * @brief The class that can be used to create a new game
 */
class Game {
private:
    Model::World world; ///< The world that is used for containing all the entities

    Control::Controller controller; ///< The controller will be used to control the game

    std::shared_ptr<Utils::Stopwatch> stopwatch = stopwatch->getStopwatch(); ///< The stopwatch of the game, is used to keep the game at a correct pace

    /**
     * @brief will display if the player has lost on the current active window
     * TODO add a check for the window if it is still open
     */
    void displayLost(sf::RenderWindow& renderWindow);

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
     * @param worldName: The filename of the world to parse
     */
    void loadWorld(const std::string& worldName);

    /**
     * @brief Plays the level currently loaded in the model
     * @param renderWindow: The window which shows the game that needs to run
     * @param sharedWorld: The world that is a shared pointer
     * @return If the level was succesfully finished
     */
    bool play(sf::RenderWindow& renderWindow, std::shared_ptr<ObserverPattern::Observer> sharedWorld);

    /**
     * @brief adds a delay to the game in order to preserve its framerate, and skips when it already passed its frame count
     */
    void wait();

    /**
     * @brief The bullet that is used to shoot from one of the ships
     * @param fileName: The name of the file from where to parse the bullets
     * @param entity: The name of the entity from which the bullet supposedly comes
     * @return The bullet in a shared ptr type
     * TODO add a check if the weakptr is valid
     * TODO add a check if the filename is valid
     */
    std::shared_ptr<Model::Bullet> createBullet(const std::string& fileName, std::weak_ptr<Model::Entity> entity);

public:

    /**
     * @brief The default game constructor
     */
    Game();

    /**
     * @brief Starts playing levels in the order they are passed through
     * @param levels: The levels that will be played in order when succesfully completed
     */
    void start(const std::vector<std::string>& levels);
};

#endif //PROJECT_SPACE_INVADERS_GAME_H
