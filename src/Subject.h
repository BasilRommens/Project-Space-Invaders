/**
 * @file Subject.h
 * @author Basil Rommens
 * @date 12/15/19
 * @brief Yoink
 */

#ifndef PROJECT_SPACE_INVADERS_SUBJECT_H
#define PROJECT_SPACE_INVADERS_SUBJECT_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <memory>

#include "Observer.h"

class Subject {
private:
    std::vector<std::shared_ptr<Observer>> observers;
protected:
    /**
     * @brief Notifies every observer held by the subject
     * @param entity: The entity on which the notification needs to be aplied
     * @param event: The event that has happened
     */
    void notify(std::shared_ptr<Entity> entity, Utils::Event event);

public:
    /**
     * @brief Adds and observer to the list of observers the subject holds
     * @param observer: The observer that will be added to the list of observers of the subject
     */
    void addObserver(std::shared_ptr<Observer> observer);

    /**
     * @brief Removes the requested observer from the class
     * @param observer: The observer that needs to be removed
     */
    void removeObserver(std::shared_ptr<Observer> observer);
};

#endif //PROJECT_SPACE_INVADERS_SUBJECT_H
