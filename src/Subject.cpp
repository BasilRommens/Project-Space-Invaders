/**
 * @file 
 * @author Basil Rommens
 * @date 12/15/19
 * @brief ...
 */

#include "Subject.h"

void Subject::addObserver(Observer* observer)
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

void Subject::removeObserver(Observer* observer)
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

void Subject::notify(const Entity& entity, Event event)
{
    for (auto observer: observers) {
        // Let observer decide what to do onNotify
    }
}
