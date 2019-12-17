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
    UPDATE_DRAW,
    MOVE_RIGHT,
    MOVE_LEFT,
    FIRE_BULLET,
    CLOSE_WINDOW
};

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
    virtual void onNotify(Event event) = 0;
};

#endif //PROJECT_SPACE_INVADERS_OBSERVER_H
