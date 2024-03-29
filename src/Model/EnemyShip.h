/**
 * @file EnemyShip.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the class EnemyShip
 */

#ifndef PROJECT_SPACE_INVADERS_ENEMYSHIP_H
#define PROJECT_SPACE_INVADERS_ENEMYSHIP_H

#include <random>

#include "Ship.h"
#include "World.h"

/**
 * @addtogroup Model
 * @{
 */
namespace Model {

/**
 * @brief This class describes an enemy ship
 */
class EnemyShip : public Ship
{
private:
        double VSpeed; ///< The distance the enemyShip will move each time it hits the border of the map in the vertical
                       ///< direction

        static double distance; ///< Variable that keeps the distance travelled by the ship

        static std::vector<std::weak_ptr<EnemyShip>> otherShips; ///< The other entemies that are in the game

        bool moved; ///< Variable to keep track if the ship already has moved (for difficulties with the observer
                    ///< pattern)

        Utils::Direction direction{Utils::Direction::LEFT}; ///< It keeps the current direction the ship is moving

        /**
         * @brief Will act on the parameters passed through and is notified by the observers
         * @param entity: The entity that is passed through and maybe used in the method
         * @param event: The event that happened and triggered this member function
         */
        void onNotify(std::shared_ptr<Entity> entity, Utils::Event event) final;

        /**
         * @brief Moves the enemyShip 1 HSpeed to the right
         * @details If the enemy ship hits the wall it will take that distance and move the other ships in the member
         * variable accordingly such that no weird travels occur
         */
        void moveRight() final;

        /**
         * @brief Moves the enemyShip 1 HSpeed to the left
         * @details If the enemy ship hits the wall it will take that distance and move the other ships in the member
         * variable accordingly such that no weird travels occur
         */
        void moveLeft() final;

        /**
         * @brief swaps the direction of the ship passed through
         * @param ship: The ship of which the direction needs to be changed
         */
        void swapDirection(std::shared_ptr<EnemyShip> ship) const;

        /**
         * @brief The function calculates a random offset for the bullet to travel and then returns it
         * @details It is based of of the framerate at which we play the game and the number of ships in the game (to
         * prevent the too much of bullets)
         * @return It returns a random offset
         */
        int randomOffset() const;

public:
        /**
         * @brief The constructor of the enemyShip
         * @param image: The image which will define the enemyships appearance
         * @param pos: The position of the enemyShip (top left corner)
         * @param health: The health of the ship
         * @param hSpeed: The horizontal speed at which the ship will travel
         * @param bulletDelay: The delay of shooting the next bullet, by a base
         * @param hitbox: The hitbox of the enemyship, used from the position (top left corner)
         * @param vSpeed: The vertical speed at which the enemyShip will move down
         * @param world: The world that the enemyShip is in
         * @throws std::domain_error If the VSpeed is negative
         */
        EnemyShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed, int bulletDelay,
                  const Utils::Hitbox& hitbox, double vSpeed, Model::World& world);

        /**
         * @return The type of the entity ("enemy")
         */
        std::string getType() const final;

        /**
         * @return The distance that one of the ships has travelled
         */
        double getDistance() const final;

        /**
         * @brief adds a ship to the other ships in the enemyship
         * @param ship: The ship that needs to be added to the other ships
         */
        static void addShip(std::weak_ptr<EnemyShip> ship);

        /**
         * @brief remove this ship from the other ships
         */
        void removeThis() final;
};
} // namespace Model
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_ENEMYSHIP_H
