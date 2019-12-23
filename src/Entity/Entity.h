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

class Observer;

namespace EntityNS {

    class Ship;

    class Entity : public Observer, public Subject, public std::enable_shared_from_this<Entity> {
    protected:
        std::string image;

        sf::Texture texture;

        Entity(const std::string& image);

        void onNotify(std::shared_ptr<EntityNS::Entity> entity, Utils::Event event) override;

    public:
        virtual ~Entity();

        Entity();

        virtual std::string getType() const;

        virtual std::shared_ptr<Utils::Position> getPos() const;

        virtual void setPosition(Utils::Position newPos);

        const sf::Texture& getTexture() const;

        const std::string& getImage() const;

        // TODO Possibly move it to the ship class
        virtual double getDamage() const;

        std::shared_ptr<Observer> getDrawShared();

        virtual std::shared_ptr<Entity> getFrom() const;

        virtual bool isInControl() const;

        virtual void setInControl();
    };

}

#endif //PROJECT_SPACE_INVADERS_ENTITY_H
