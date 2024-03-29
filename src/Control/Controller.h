/**
 * @file Controller.h
 * @author Basil Rommens
 * @date 12/17/19
 * @brief The header file of the class Controller
 */

#ifndef PROJECT_SPACE_INVADERS_CONTROLLER_H
#define PROJECT_SPACE_INVADERS_CONTROLLER_H

#include <SFML/Graphics.hpp>

#include "../Model/World.h"
#include "../utils/ObserverPattern/Observer.h"
#include "../utils/ObserverPattern/Subject.h"

/**
 * @namespace Control The namespace Control can be used to indicate the parts of the control
 */

/**
 * @addtogroup Control
 * @{
 */
namespace Control {

/**
 * @brief The class that is used to control the whole game during one game tick iteration
 */
class Controller : public ObserverPattern::Subject
{
private:
        /**
         * @brief removes all the observers that arent found anymore in the world as entities
         * @param world: The world in which to check for entities
         */
        void removeUnnecessaryObservers(std::shared_ptr<Model::World> world);

public:
        /**'
         * @brief handles the input
         * @param window: The window that is used for graphically displaying the game
         * @param world: The world that is used to view all the entities and use them
         */
        void handleInput(sf::RenderWindow& window, std::shared_ptr<Model::World> world);

        /**
         * @brief updates the world with the bullets and the enemy ships
         * @param world: The world that needs to be updated
         */
        void update(std::shared_ptr<Model::World> world);

        /**
         * @brief This function serves as a loop to wait for players input to restart the game
         * @param renderWindow: The window which renders the game
         * @return If the game can be replayed
         */
        bool replay(sf::RenderWindow& renderWindow);
};

} // namespace Control
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_CONTROLLER_H
