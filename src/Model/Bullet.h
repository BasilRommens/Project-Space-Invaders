/**
 * @file Bullet.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the Bullet class
 */

#ifndef PROJECT_SPACE_INVADERS_BULLET_H
#define PROJECT_SPACE_INVADERS_BULLET_H

#include "../utils/Hitbox.h"
#include "../utils/Position.h"
#include "Entity.h"
#include "Ship.h"

/**
 * @addtogroup Model
 * @{
 */
namespace Model {

/**
 * @brief The class that describes a bullet
 */
class Bullet : public Entity
{
private:
        Utils::Direction direction; ///< The direction in which the bullet is travelling
        double speed;               ///< The speed at which the bullet is travelling
        double damage;              ///< The damage the bullet will make when it hits an entity
        Utils::Position pos;        ///< The position of the bullet
        std::weak_ptr<Entity>
            from;              ///< The entity that has created the bullet it is a weak pointer because it doesnt own it
        bool inControl{false}; ///< Is a member variable to check if it is already in the controller class
        Utils::Hitbox hitbox;  ///< The hitbox of the bullet measured from the top left of the sprite
public:
        /**
         * @brief constructor that makes another bullet based on another bullet that is passed through via a shared
         * pointer
         * @param other: The name of the other bullet that is to be copied
         */
        Bullet(std::shared_ptr<Bullet> other);

        /**
         * @brief The constructor of the Bullet class
         * @param image: The image that will be used as the representation of the bullet
         * @param direction: The direction in which we want the bullet to travel (UP or DOWN)
         * @param speed: THe speed at which we expect to have the bullet to move
         * @param damage: The damage the bullet is expected to do
         * @param pos: The position at which we can find the bullet
         * @param from: The entity that is shooting this particular bullet with a weak pointer
         */
        Bullet(const std::string& image, Utils::Direction direction, double speed, double damage,
               const Utils::Position& pos, std::weak_ptr<Entity> from, Utils::Hitbox hitbox);

        /**
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

        /**
         * @return if the object itself can be collided with other entities
         */
        bool collidable() const final;

        /**
         * @return The amount of damage the bullet can do
         */
        double getDamage() const final;

        /**
         * @return The direction in which the bullet is travelling
         */
        Utils::Direction getDirection() const final;

        /**
         * @return The hitbox of the bullet
         */
        const Utils::Hitbox& getHitbox() const final;
};

} // namespace Model
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_BULLET_H
