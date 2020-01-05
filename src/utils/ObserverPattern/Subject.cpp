/**
 * @file 
 * @author Basil Rommens
 * @date 12/15/19
 * @brief ...
 */

#include "Subject.h"

void ObserverPattern::Subject::addObserver(std::shared_ptr<Observer> observer)
{
    try {
        if (!observer) {
            throw std::invalid_argument(
                    "No observer has been passed through in the method addObserver from the class Subject");
        }
        observers.push_back(observer);
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void ObserverPattern::Subject::removeObserver(std::shared_ptr<Observer> observer)
{
    try {
        if (!observer) {
            throw std::invalid_argument(
                    "No observer has been passed through in the method removeObserver from the class Subject");
        }
        // Variable that checks if the observer has been found
        bool found{false};
        std::vector<std::shared_ptr<Observer>>::iterator observerIt;
        for (observerIt = observers.begin(); observerIt!=observers.end(); ++observerIt) {
            if (*observerIt==observer) {
                found = true;
                break;
            }
        }
        // If we have found the observer to delete then delete it
        if (found) {
            observers.erase(observerIt);
        }
        std::cout << observer.use_count() << std::endl;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void ObserverPattern::Subject::notify(std::shared_ptr<Model::Entity> entity, Utils::Event event)
{
    for (std::shared_ptr<Observer> observer: observers) {
        // Let observer decide what to do onNotify
        observer->onNotify(entity, event);
    }
}

const std::vector<std::shared_ptr<ObserverPattern::Observer>>& ObserverPattern::Subject::getObservers() const
{
    return observers;
}

ObserverPattern::Subject::~Subject()
{
    for (auto observer: observers) {
        observer.reset();
    }
    observers.clear();
}

std::shared_ptr<ObserverPattern::Observer> ObserverPattern::Subject::retrieveObserver(const std::string typeName) const
{
    // TODO fix false code
    return observers[0];
    for (auto observer: observers) {
        std::string type = observer.get()->getType();
        if (type=="world") {
            return observer;
        }
    }
    return nullptr;
}
