/**
 * @file Observer.h
 * @author Basil Rommens
 * @date 12/15/19
 * @brief The header file of the Observer class
 */

#ifndef PROJECT_SPACE_INVADERS_OBSERVER_H
#define PROJECT_SPACE_INVADERS_OBSERVER_H

#include <memory>

#include "utils/Event.h"

namespace EntityNS {

    class Entity;

}

class Observer {
public:
    /**
     * @brief Destructor of the Observer
     */
    virtual ~Observer();

    /**
     * @brief A pure virtual function that needs to act accordingly when certain events are passed through
     * @param event: The event that took place
     */
    virtual void onNotify(std::shared_ptr<EntityNS::Entity> entity, Utils::Event event) = 0;

    virtual std::string getType();
};

#endif //PROJECT_SPACE_INVADERS_OBSERVER_H
