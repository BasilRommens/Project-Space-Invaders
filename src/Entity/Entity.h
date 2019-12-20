/**
 * @file Entity.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the Entity class
 */

#ifndef PROJECT_SPACE_INVADERS_ENTITY_H
#define PROJECT_SPACE_INVADERS_ENTITY_H

#include <string>

#include "../Observer.h"
#include "../Subject.h"
#include "../utils/Position.h"

class Observer;

class Entity : public Observer, public Subject {
protected:
    std::string image;

    Entity(const std::string& image);

    void onNotify(std::shared_ptr<Entity> entity, Utils::Event event) override;

public:
    Entity();

    virtual std::string getType() const;

    virtual Utils::Position getPos() const;

    const std::string& getImage() const;
};

#endif //PROJECT_SPACE_INVADERS_ENTITY_H
