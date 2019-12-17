/**
 * @file 
 * @author Basil Rommens
 * @date 12/15/19
 * @brief The header file of the Observer class
 */

#ifndef PROJECT_SPACE_INVADERS_OBSERVER_H
#define PROJECT_SPACE_INVADERS_OBSERVER_H

#include "utils/Event.h"

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
    virtual void onNotify(Utils::Event event) = 0;
};

#endif //PROJECT_SPACE_INVADERS_OBSERVER_H
