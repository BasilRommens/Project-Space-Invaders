/**
 * @file Game.h
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The header file of the class Game
 */

#ifndef PROJECT_SPACE_INVADERS_GAME_H
#define PROJECT_SPACE_INVADERS_GAME_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include "Control/Controller.h"
#include "Model/Bullet.h"
#include "Model/EnemyShip.h"
#include "Model/PlayerShip.h"
#include "Model/World.h"
#include "View/Draw.h"
#include "utils/Global.h"
#include "utils/Stopwatch.h"
#include "utils/json.hpp"

class GameParser;

/**
 * @brief The class that can be used to create a new game
 */
class Game
{
private:
        friend GameParser; ///< used to simplify code writing, prone to errors (without get/set)

        std::shared_ptr<ObserverPattern::Observer>
            worldObserver; ///< The world that is used for containing all the entities is a shared pointer because it is
                           ///< used later

        Control::Controller controller; ///< The controller will be used to control the game

        std::shared_ptr<Utils::Stopwatch> stopwatch =
            stopwatch->getStopwatch(); ///< The stopwatch of the game, is used to keep the game at a correct pace

        /**
         * @brief will display the text passed through on the current active window
         * @param textToDisplay: The text that will be displayed on the window
         * @param renderWindow: The renderWindow on which to display the message
         * @throws std::runtime_error If the font that is used isn't in the project then error
         */
        void displayText(const std::string& textToDisplay, sf::RenderWindow& renderWindow) const;

        /**
         * @brief will display that the player has lost on the current active window
         * @param renderWindow: The window on which to display the losing message
         */
        void displayLost(sf::RenderWindow& renderWindow) const;

        /**
         * @brief will display that the player has lost on the current active window
         * @param renderWindow: The window on which to display the winning message
         */
        void displayWon(sf::RenderWindow& renderWindow) const;

        /**
         * @brief Plays the level currently loaded in the model
         * @param renderWindow: The window which shows the game that needs to run
         * @param sharedWorld: The world that is a shared pointer
         * @return If the level was succesfully finished
         */
        bool play(sf::RenderWindow& renderWindow);

        /**
         * @brief adds a delay to the game in order to preserve its framerate, and skips when it already passed its
         * frame count
         */
        void wait() const;

public:
        /**
         * @brief The default game constructor
         */
        Game() = default;

        /**
         * @brief Starts playing levels in the order they are passed through
         * @param levels: The levels that will be played in order when succesfully completed
         */
        void start(const std::vector<std::string>& levels);
};

#endif // PROJECT_SPACE_INVADERS_GAME_H
