/**
 * @file 
 * @author Basil Rommens
 * @date 12/15/19
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_SUBJECT_H
#define PROJECT_SPACE_INVADERS_SUBJECT_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>

#include "Observer.h"

class Subject {
private:
    std::vector<Observer*> observers;
protected:
    void notify(const Entity& entity, Event event);

public:
    void addObserver(Observer* observer);

    void removeObserver(Observer* observer);
};

#endif //PROJECT_SPACE_INVADERS_SUBJECT_H
