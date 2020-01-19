/**
 * @file Subject.h
 * @author Basil Rommens
 * @date 12/15/19
 * @brief The header file of the Subject class
 */

#ifndef PROJECT_SPACE_INVADERS_SUBJECT_H
#define PROJECT_SPACE_INVADERS_SUBJECT_H

#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

#include "Observer.h"

/**
 * @addtogroup ObserverPattern
 * @{
 */
namespace ObserverPattern {

/**
 * @brief The subject class is created so that it can notify each of its observers if something interesting happens
 */
class Subject
{
private:
        std::vector<std::shared_ptr<Observer>> observers;

protected:
        /**
         * @brief Notifies every observer held by the subject
         * @param entity: The entity on which the notification needs to be aplied
         * @param event: The event that has happened
         */
        void notify(std::shared_ptr<Model::Entity> entity, Utils::Event event);

        /**
         * @return The observers of the subject
         */
        const std::vector<std::shared_ptr<Observer>>& getObservers() const;

        /**
         * @brief Searches and returns the observer by the type that is asked
         * @param typeName: The name of the type that is searched
         * @return The observer item of that type
         */
        std::shared_ptr<Observer> retrieveObserver(const std::string& typeName) const;

public:
        /**
         * @brief The default destructor of a subject
         */
        virtual ~Subject();

        /**
         * @brief Adds and observer to the list of observers the subject holds
         * @param observer: The observer that will be added to the list of observers of the subject
         * @throws std::invalid_argument This exception will be thrown whenever we try to add an observer that points to
         * nothing
         */
        void addObserver(std::shared_ptr<Observer> observer);

        /**
         * @brief Removes the requested observer from the class
         * @param observer: The observer that needs to be removed
         * @throws std::invalid_argument We throw this exception whenever we want to remove an empty observer from the
         * list of observers
         */
        void removeObserver(std::shared_ptr<Observer> observer);

        /**
         * @brief clears all the observers from the subject
         */
        void clearObservers();
};

} // namespace ObserverPattern
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_SUBJECT_H
