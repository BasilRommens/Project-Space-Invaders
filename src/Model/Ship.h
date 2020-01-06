/**
 * @file Ship.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the class Ship
 */

#ifndef PROJECT_SPACE_INVADERS_SHIP_H
#define PROJECT_SPACE_INVADERS_SHIP_H

#include <iostream>
#include <memory>

#include "Entity.h"
#include "../utils/Position.h"
#include "Bullet.h"

namespace Model {

    class World;

    class Ship : public Entity {
    protected:
        Utils::Position pos; ///< The current position, top right corner, of the ship in the coordinate system that is decided by the variables in utils as upper...
        double health; ///< The health of the ship
        double HSpeed; ///< The horizontal speed at which the ship can move
        // TODO make the bullet delay in the input files
        const int bulletDelay{30}; ///< The time a ship must wait before it can shoot another bullet
        int currentDelay; ///< The delay which can be reset when there is a bullet shot if the counter = 0
        Utils::Hitbox hitbox; ///< The hitbox that the ship posseses
        std::shared_ptr<Bullet> dummyBullet; ///< The dummybullet of the ship which is used to make a new bullet that can be shot from the ship
        std::weak_ptr<World> world; ///< Needed to update the world if there are bullets shot

        /**
         * @brief a pure virtual member function to move the ship right
         */
        virtual void moveRight() = 0;

        /**
         * @brief a pure virtual member function to move the ship left
         */
        virtual void moveLeft() = 0;

        /**
         * @brief a pure virtual member function to let the ship fire a bullet
         */
        virtual void fireBullet() = 0;

        /**
         * @brief Resets the current delay of the ship to fire a bullet
         */
        void resetDelay();

        /**
         * @brief decreases the current delay by one with each frame controlled by the controller
         * @details Stops at 0 to prevent problems
         */
        void decreaseDelay();

    public:
        /**
         * @brief The destructor of a ship
         */
        virtual ~Ship();

        /**
         * @brief The constructor of a ship
         * @param image: The image which is used for the texture of the ship
         * @see Model.h
         * @param pos: The position of the ship (Top left corner)
         * @param health: The health of the ship
         * @param hSpeed: The horizontal speed at which the ship will move
         * @param bulletDelay: The standard delay of the ship
         * @param hitbox: The hitbox of the ship which is measured from the top left corner
         * TODO add the necessary checks
         */
        Ship(const std::string& image, const Utils::Position& pos, double health, double hSpeed,
                int bulletDelay, const Utils::Hitbox& hitbox);

        /**
         * @return The type of the entity ("ship")
         */
        std::string getType() const override;

        /**
         * @return The position of the ship
         */
        std::shared_ptr<Utils::Position> getPos() const final;

        /**
         * @brief sets the new position of the current ship according to the parameter passed through
         * @param newPos: The position to set for the ship
         * TODO add a check to check if the new position is valid in the new system
         */
        void setPosition(Utils::Position newPos) final;

        /**
         * @return The hitbox of the object of the ship
         */
        const Utils::Hitbox& getHitbox() const final;

        /**
         * @brief adds a dummy bullet to the ship
         * @param dummyBullet: The bullet which to shoot when asked to shoot with the current position taken in account
         */
        void addBullet(std::shared_ptr<Bullet> dummyBullet) final;

        /**
         * @return Creates a new bullet instance that can be shot from the ship to be shot at the other ships
         */
        std::shared_ptr<Model::Entity> spawnBullet() final;

        /**
         * @return The dummy bullet that can be used to recreate in another ship entity
         */
        std::shared_ptr<Bullet> getDummyBullet() const final;

        /**
         * @brief applies the damage that is passed through to the current ship
         * @param damage: The damage that needs to be applied to the current ship
         */
        void doDamage(double damage) final;

        /**
         * @return that the ship is collidable with collidable objects
         */
        bool collidable() const final;

        /**
         * @return The current health status of the ship
         */
        double getHealth() const;

        /**
         * @return The amount of time that is left before the ship can shoot another bullet
         */
        int getCurrentDelay() const final;

        /**
         * @brief adds the world that needs to be updated for bullets
         * @param worldToAdd: The world in which the ship resides
         */
        void addWorld(std::shared_ptr<Model::Entity> worldToAdd);
    };

}

#endif //PROJECT_SPACE_INVADERS_SHIP_H
