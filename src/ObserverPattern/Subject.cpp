/**
 * @file 
 * @author Basil Rommens
 * @date 12/15/19
 * @brief ...
 */

#include "Subject.h"

void Subject::addObserver(std::shared_ptr<Observer> observer)
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

void Subject::removeObserver(std::shared_ptr<Observer> observer)
{
    try {
        if (!observer) {
            throw std::invalid_argument(
                    "No observer has been passed through in the method removeObserver from the class Subject");
        }
        observers.erase(std::find(observers.begin(), observers.end(), observer));
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Subject::notify(std::shared_ptr<EntityNS::Entity> entity, Utils::Event event)
{
    for (std::shared_ptr<Observer> observer: observers) {
        // Let observer decide what to do onNotify
        observer->onNotify(entity, event);
    }
}

const std::vector<std::shared_ptr<Observer>>& Subject::getObservers() const
{
    return observers;
}

Subject::~Subject()
{
    for (auto observer: observers) {
        observer.reset();
    }
}
