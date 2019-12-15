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
    virtual ~Observer();

    virtual void onNotify(const Entity& entity, Event event) = 0;
};

#endif //PROJECT_SPACE_INVADERS_OBSERVER_H
