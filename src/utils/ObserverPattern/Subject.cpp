/**
 * @file Subject.cpp
 * @author Basil Rommens
 * @date 12/15/19
 * @brief The cpp file of the class Subject
 */

#include "Subject.h"
#include "../../Model/World.h"

void ObserverPattern::Subject::addObserver(std::shared_ptr<Observer> observer)
{
        try {
                if (!observer) {
                        throw std::invalid_argument(
                            "No observer has been passed through in the method addObserver from the class Subject");
                }
                observers.push_back(observer);
        } catch (std::exception& e) {
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
                // Loop till the iterator of the observer has been found, if not then it will do nothing
                for (auto observerIt = observers.begin(); observerIt != observers.end(); ++observerIt) {
                        if (*observerIt == observer) {
                                observers.erase(observerIt);
                                break;
                        }
                }
        } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
        }
}

void ObserverPattern::Subject::notify(std::shared_ptr<Model::Entity> entity, Utils::Event event)
{
        for (std::shared_ptr<Observer> observer : observers) {
                // Let observer decide what to do onNotify
                observer->onNotify(entity, event);
        }
}

const std::vector<std::shared_ptr<ObserverPattern::Observer>>& ObserverPattern::Subject::getObservers() const
{
        return observers;
}

ObserverPattern::Subject::~Subject() { observers.clear(); }

std::shared_ptr<ObserverPattern::Observer> ObserverPattern::Subject::retrieveObserver(const std::string& typeName) const
{
        for (auto observer : observers) {
                try {
                        // try to downcast to world in order to get the correct type that way
                        std::static_pointer_cast<Model::World>(observer);
                        return observer;
                }catch (...) {
                        // Do nothing
                }
        }
        return nullptr;
}

void ObserverPattern::Subject::clearObservers() { observers.clear(); }
