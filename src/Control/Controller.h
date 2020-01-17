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
    void removeUnnecessaryObservers(std::shared_ptr<Model::World> world);
public:
        /**'
         * @brief runs the controller during one game tick
         * @param window: The window that is used for graphically displaying the game
         * @param world: The world that is used to view all the entities and use them
         */
        void run(sf::RenderWindow& window, std::shared_ptr<Model::World> world);
};

} // namespace Control
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_CONTROLLER_H
