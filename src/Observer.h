/**
 * @file 
 * @author Basil Rommens
 * @date 12/15/19
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_OBSERVER_H
#define PROJECT_SPACE_INVADERS_OBSERVER_H

#include "Entity/Entity.h"

enum Event {
    UPDATE_DRAW
};

class Observer {
public:
    /**
     * @brief Destructor of the Observer
     */
    virtual ~Observer();

    /**
     * @brief A pure virtual function that needs to act accordingly when certain events are passed through
     * @param entity: The entity that is needed for the event
     * @param event: The event that took place
     */
    virtual void onNotify(const Entity& entity, Event event) = 0;
};

#endif //PROJECT_SPACE_INVADERS_OBSERVER_H
