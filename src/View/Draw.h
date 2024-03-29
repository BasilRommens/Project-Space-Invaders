/**
 * @file Draw.h
 * @author Basil Rommens
 * @date 12/20/19
 * @brief The header file of the class Draw
 */

#ifndef PROJECT_SPACE_INVADERS_DRAW_H
#define PROJECT_SPACE_INVADERS_DRAW_H

#include <SFML/Graphics.hpp>
#include <map>

#include "../Model/Bullet.h"
#include "../Model/EnemyShip.h"
#include "../Model/Entity.h"
#include "../Model/PlayerShip.h"
#include "../utils/Transformation.h"

/**
 * @addtogroup Model
 * @{
 */
namespace Model {

class World;
}
/**
 * @}
 */

/**
 * @namespace View We can use this namespace to indicate that we are in the view part of the MVC pattern
 */

/**
 * @addtogroup View
 * @{
 */
namespace View {

/**
 * @brief This class can be used to draw something on the display with sprites
 */
class Draw : public ObserverPattern::Observer
{
private:
        bool open{true}; ///< is a variable to check if the window still is open

        std::map<std::string, std::shared_ptr<sf::Texture>>
            textures; ///< Contains all the textures of all the sprites used in the game, based on a map

        std::shared_ptr<sf::RenderWindow> window; ///< The window at which we can view what happens

        std::vector<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>>>
            sprites; ///< The collection of sprites and entities related with them

        /**
         * @brief makes a new sprite based of of the entity that is passed through uses the texture that it gives back
         * @param entity: The entity that should be made to a fitting texture
         * @return The sprite that needs to be placed on the screen
         */
        sf::Sprite createSprite(std::shared_ptr<Model::Entity> entity);

        /**
         * @brief Says to update the position of the entity
         * @param entity: The entity that needs to be updated
         * @throws std::invalid_argument if no entity is to be found as an argument
         */
        void updateD(std::shared_ptr<Model::Entity> entity);

        /**
         * @brief says that the entity needs to be added to hte
         * @param entity: The entity that needs to be created as a sprite and displayed
         * @throws std::invalid_argument if no entity is to be found as an argument
         */
        void newD(std::shared_ptr<Model::Entity> entity);

public:
        /**
         * @brief destructor of draw
         */
        ~Draw() final;

        /**
         * @brief The constructor of Draw
         * @param window: The window in which we will draw all the sprites
         * @param world: The world which is used for adding the entities
         * @throws std::invalid_argument If no window or world is passed
         */
        Draw(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Model::World> world);

        /**
         * @brief The function inherited from the class Observer, used to receive notifications from their subjects
         * @param entity: The entity that is used in the notification
         * @param event: The event that happened and triggered the notification
         */
        void onNotify(std::shared_ptr<Model::Entity> entity, Utils::Event event) final;

        /**
         * @brief make the current sprites visible on the display
         */
        void view() const;

        /**
         * @brief adds a sprite to the draw via the parameter
         * @param sprite: The sprite that needs to be added to the sprites member variable
         */
        void addSprite(std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>>& sprite);

        /**
         * @brief deletes the entity from the sprites with the corresponding entity pointer
         * @param entityToRemove: The entity that needs to be removed from the sprites
         */
        void removeSprite(std::shared_ptr<Model::Entity> entityToRemove);

        /**
         * @return The type of the observer ("draw")
         * @details must be implemented because the getType function is pure virtual in the observer class
         */
        std::string getType() const final;

        /**
         * @return true if the window is open otherwise it is closed
         */
        bool isOpen() const;
};

} // namespace View
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_DRAW_H
