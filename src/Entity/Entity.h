/**
 * @file Entity.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the Entity class
 */

#ifndef PROJECT_SPACE_INVADERS_ENTITY_H
#define PROJECT_SPACE_INVADERS_ENTITY_H

#include <string>
#include <SFML/Graphics.hpp>

#include "../Utils/ObserverPattern/Observer.h"
#include "../Utils/ObserverPattern/Subject.h"
#include "../utils/Position.h"
#include "../Hitbox.h"

class Observer;
/**
 * @addtogroup Model
 * @{
 */
/// TODO clean up this fucking mess of a class by casting pointers
namespace Model {

    class Ship;

    class Bullet;

    class Entity
            : public ObserverPattern::Observer,
              public ObserverPattern::Subject,
              public std::enable_shared_from_this<Entity> {
    protected:
        std::string image; ///< The image string which will represent the entity

        sf::Texture texture; ///< The texture of the Entity (faster moving of sprites)

        /**
         * @brief the protected entity constructor because it is an abstract class
         * @param image: The image that needs to be used for the entity
         */
        // TODO check if the image is correct otherwise throw an error
        explicit Entity(const std::string& image);

        /**
         * @brief The onNotify of an abstract entity, does nothing
         * @param entity: The entity on which needs to be reacted
         * @param event: The event that has happened
         */
        void onNotify(std::shared_ptr<Model::Entity> entity, Utils::Event event) override;

    public:
        /**
         * @brief The entity constructor specifically made for the constructing a bullet from a shared pointer
         * @param other: The other entity to initialize, is specific for the bullet so that it also gets called when the bullet constructor is called for correctly copying it
         */
        explicit Entity(std::shared_ptr<Bullet> other);

        /**
         * @brief The destructor of this Entity class
         */
        ~Entity() override;

        /**
         * @brief The default constructor of the Entity class
         */
        Entity();

        /**
         * @return The type of the entity ("")
         */
        virtual std::string getType() const;

        /**
         * @return The position of the entity
         */
        virtual std::shared_ptr<Utils::Position> getPos() const;

        /**
         * @brief Will set the position of the entity
         * @param newPos: The new position of the entity
         */
        // TODO check if the postion is valid
        virtual void setPosition(Utils::Position newPos);

        /**
         * @return The texture of the Entity for quick sprite creation
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
         * @return The shared draw of the world class
         */
        std::shared_ptr<ObserverPattern::Observer> getDrawShared();

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
         * @detail It is a static variable that is set by the ship that has travelled the least distance. It is used in the case where one of the ships has hit the screen border
         */
        virtual double getDistance() const;

        /**
         * @return The hitbox of an entity if it has one
         */
        virtual const Hitbox& getHitbox() const;

        /**
         * @see Ship.h
         * @brief Adds a dummy bullet to one of the ship entities as a base to create bullets from more easily
         * @param dummyBullet: The bullet that is used as a base to shoot bullets into the void
         * TODO check that the dummy bullet is of the class
         */
        virtual void addBullet(std::shared_ptr<Bullet> dummyBullet);

        /**
         * @see Ship.h
         * @return Creates a bullet based on the current position of the ship
         * TODO check if the dummy bullet exists
         */
        virtual std::shared_ptr<Entity> spawnBullet();

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
    };

}
/**
 * @}
 */

#endif //PROJECT_SPACE_INVADERS_ENTITY_H
