/**
 * @file PlayerShip.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the class PlayerShip
 */

#ifndef PROJECT_SPACE_INVADERS_PLAYERSHIP_H
#define PROJECT_SPACE_INVADERS_PLAYERSHIP_H

#include "Ship.h"

namespace Model {

    /**
     * @brief The ship that is the ship controlled by the player
     */
    class PlayerShip : public Ship {
    private:
        /**
         * @brief will be notified by all the subjects that contain the player ship in it
         * @param entity: The entity that is used in the member function
         * @param event: The event on which the player ship is notified
         */
        void onNotify(std::shared_ptr<Entity> entity, Utils::Event event) final;

        /**
         * @brief Moves the player ship to the right
         */
        void moveRight();

        /**
         * @brief Moves the player ship to the left
         */
        void moveLeft();

        /**
         * @brief fires a bullet from the current position of the player ship
         */
        void fireBullet() final;

    public:
        /**
         * @brief The destructor of the player ship
         */
        virtual ~PlayerShip();

        /**
         * @brief The constructor of the player ship
         * @param image: The image which will be used to determine the player ships texture
         * @param pos: The position of the player ship, the top left corner
         * @param health: The health of the player ship
         * @param hSpeed: The horizontal speed at which the player ship will move
         * @param bulletDelay: The maximum delay the bullet needs to wait after each reload
         * @param hitbox: The hitbox of the current player ship
         */
        PlayerShip(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
                int bulletDelay, const Utils::Hitbox& hitbox);

        /**
         * @return The type of the entity ("player")
         */
        std::string getType() const final;
    };

}

#endif //PROJECT_SPACE_INVADERS_PLAYERSHIP_H