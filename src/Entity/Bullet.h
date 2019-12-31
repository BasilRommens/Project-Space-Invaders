/**
 * @file Bullet.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the Bullet class
 */

#ifndef PROJECT_SPACE_INVADERS_BULLET_H
#define PROJECT_SPACE_INVADERS_BULLET_H

#include "Entity.h"
#include "Ship.h"
#include "../Hitbox.h"
#include "../utils/Position.h"

/**
 * @addtogroup Model
 * @{
 */
namespace Model {

    class Bullet : public Entity {
    private:
        Utils::Direction direction; ///< The direction in which the bullet is travelling
        double speed; ///< The speed at which the bullet is travelling
        double damage; ///< The damage the bullet will make when it hits an entity
        Utils::Position pos; ///< The position of the bullet
        std::weak_ptr<Entity> from; ///< The entity that has created the bullet it is a weak pointer because it doesnt own it
        bool inControl{false}; ///< Is a member variable to check if it is already in the controller class
        Hitbox hitbox;
    public:
        Bullet(std::shared_ptr<Bullet> other);

        /**
         * @brief The destructor of the Bullet class
         */
        virtual ~Bullet();

        /**
         * @brief The constructor of the Bullet class
         * @param image: The image that will be used as the representation of the bullet
         * @param direction: The direction in which we want the bullet to travel (UP or DOWN)
         * @param speed: THe speed at which we expect to have the bullet to move
         * @param damage: The damage the bullet is expected to do
         * @param pos: The position at which we can find the bullet
         * @param from: The entity that is shooting this particular bullet with a weak pointer
         */
        // TODO use RAII
        // TODO add assertion for bullet direction
        // TODO add assertion for bullet speed
        // TODO add assertion for bullet damage
        // TODO add assertion for pos
        // TODO add assertion for from
        Bullet(const std::string& image, Utils::Direction direction, double speed, double damage,
                const Utils::Position& pos, std::weak_ptr<Entity> from, Hitbox hitbox);

        /**
         *
         * @return The type of the entity ("Bullet")
         */
        std::string getType() const final;

        /**
         * @return The position with a shared pointer of the bullet
         */
        std::shared_ptr<Utils::Position> getPos() const final;

        /**
         * @brief Will set the bullets position
         * @param newPos: The new position of the bullet
         */
        void setPosition(Utils::Position newPos) final;

        /**
         * @return The entity that has shot the bullet
         */
        std::weak_ptr<Entity> getFrom() const final;

        /**
         * @return If the bullet is in the controller via the observer pattern
         */
        bool isInControl() const final;

        /**
         * @brief Sets the control to true
         */
        void setInControl() final;

        /**
         * @brief will be triggered when the subjects calls all of its observers
         * @param entity: The entity that is passed through
         * @param event: The event that happened and is passed trough
         */
        void onNotify(std::shared_ptr<Entity> entity, Utils::Event event) final;

        bool collidable() const final;
    };

}
/**
 * @}
 */

#endif //PROJECT_SPACE_INVADERS_BULLET_H
