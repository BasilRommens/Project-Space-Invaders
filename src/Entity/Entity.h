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

#include "../ObserverPattern/Observer.h"
#include "../ObserverPattern/Subject.h"
#include "../utils/Position.h"
#include "../Hitbox.h"

class Observer;
/**
 * @addtogroup EntityNS
 * @{
 */

namespace EntityNS {

    class Ship;

    class Bullet;

    class Entity : public Observer, public Subject, public std::enable_shared_from_this<Entity> {
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
        void onNotify(std::shared_ptr<EntityNS::Entity> entity, Utils::Event event) override;

    public:
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

        std::shared_ptr<Observer> getDrawShared();

        virtual std::weak_ptr<Entity> getFrom() const;

        virtual bool isInControl() const;

        virtual void setInControl();

        virtual double getDistance() const;

        virtual const Hitbox& getHitbox() const;

        virtual void addBullet(std::shared_ptr<Bullet> dummyBullet);

        virtual std::shared_ptr<Entity> spawnBullet();
    };

}
/**
 * @}
 */

#endif //PROJECT_SPACE_INVADERS_ENTITY_H
