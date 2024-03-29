/**
 * @file Entity.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the Entity class
 */

#ifndef PROJECT_SPACE_INVADERS_ENTITY_H
#define PROJECT_SPACE_INVADERS_ENTITY_H

#include <SFML/Graphics.hpp>
#include <string>

#include "../utils/Hitbox.h"
#include "../utils/ObserverPattern/Observer.h"
#include "../utils/ObserverPattern/Subject.h"
#include "../utils/Position.h"

/**
 * @namespace Model This namespace exists to indicate all the entities in the game
 */

/**
 * @addtogroup Model
 * @{
 */
namespace Model {

class Ship;

class Bullet;

class World;

/**
 * @brief is the superclass of all the possible entities in the game
 */
/// TODO clean up this fucking mess of a class by casting pointers
class Entity : public ObserverPattern::Observer,
               public ObserverPattern::Subject,
               public std::enable_shared_from_this<Entity>
{
private:
        std::string image; ///< The image string which will represent the entity

        sf::Texture texture; ///< The texture of the Model (faster moving of sprites)

protected:
        /**
         * @brief the protected entity constructor because it is an abstract class
         * @param image: The image that needs to be used for the entity
         * @throws std::exception In fact i do not know this type of exception
         */
        explicit Entity(const std::string& image);

        /**
         * @brief The onNotify of an abstract entity, does nothing
         * @param entity: The entity on which needs to be reacted
         * @param event: The event that has happened
         */
        void onNotify(std::shared_ptr<Model::Entity> entity, Utils::Event event) override;

public:
        /**
         * @brief The destructor of this Model class
         */
        ~Entity() override = default;

        /**
         * @brief The default constructor of the Model class
         */
        Entity() = default;

        /**
         * @return The type of the entity ("")
         */
        std::string getType() const override;

        /**
         * @return The position of the entity
         */
        virtual std::shared_ptr<Utils::Position> getPos() const;

        /**
         * @brief Will set the position of the entity
         * @param newPos: The new position of the entity
         * @see Ship.h
         */
        virtual void setPosition(Utils::Position newPos);

        /**
         * @return The texture of the Model for quick sprite creation
         */
        const sf::Texture& getTexture() const;

        /**
         * @return The image string
         */
        const std::string& getImage() const;

        // TODO Possibly move it to the ship class
        /**
         * @return The damage done by a bullet
         */
        virtual double getDamage() const;

        /**
         * @see Bullet.h
         * @return where the bullet comes from
         */
        virtual std::weak_ptr<Entity> getFrom() const;

        /**
         * @see Bullet.h
         * @return If the object itself already has been through the control and is being observed
         */
        virtual bool isInControl() const;

        /**
         * @see Bullet.h
         * @brief Sets the control member variable to true to indicate it is observed by the control
         */
        virtual void setInControl();

        /**
         * @see EnemyShip.h
         * @return The distance that an enemyship has travelled in one step
         * It is a static variable that is set by the ship that has travelled the least distance. It is used in
         * the case where one of the ships has hit the screen border
         */
        virtual double getDistance() const;

        /**
         * @return The hitbox of an entity if it has one
         */
        virtual const Utils::Hitbox& getHitbox() const;

        /**
         * @see Ship.h
         * @brief Adds a dummy bullet to one of the ship entities as a base to create bullets from more easily
         * @param dummyBullet: The bullet that is used as a base to shoot bullets into the void
         */
        virtual void addBullet(std::shared_ptr<Bullet> dummyBullet);

        /**
         * @see Ship.h
         * @return Creates a bullet based on the current position of the ship
         */
        virtual std::shared_ptr<Entity> spawnBullet() const;

        /**
         * @see Ship.h
         * @return The dummy bullet of the ship
         */
        virtual std::shared_ptr<Bullet> getDummyBullet() const;

        /**
         * @see Ship.h
         * @brief applies the damage that is passed through to the ship
         * @param damage: The damage that needs to be done to the ship
         */
        virtual void doDamage(double damage);

        /**
         * @return If the entity can be collided with
         */
        virtual bool collidable() const;

        /**
         * @see Ship.h
         * @return The health of the current ship
         */
        virtual double getHealth() const;

        /**
         * @see Ship.h
         * @return The delay that the bullet has before being shot again
         */
        virtual int getCurrentDelay() const;

        /**
         * @see EnemyShip.h
         * @brief Remove the ship from the list of otherShips
         */
        virtual void removeThis();

        /**
         * @see Bullet.h
         * @return The direction in which an entity is travelling
         */
        virtual Utils::Direction getDirection() const;
};

} // namespace Model
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_ENTITY_H
