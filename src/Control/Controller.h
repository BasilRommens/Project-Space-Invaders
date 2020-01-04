/**
 * @file Controller.h
 * @author Basil Rommens
 * @date 12/17/19
 * @brief The header file of the class Controller
 */

#ifndef PROJECT_SPACE_INVADERS_CONTROLLER_H
#define PROJECT_SPACE_INVADERS_CONTROLLER_H

#include <SFML/Graphics.hpp>

#include "Utils/ObserverPattern/Subject.h"
#include "Utils/ObserverPattern/Observer.h"
#include "../Entity/World.h"

namespace Control {

    class Controller : public ObserverPattern::Subject {
    public:
        void run(sf::RenderWindow& window, Model::World& world);
    };

}

#endif //PROJECT_SPACE_INVADERS_CONTROLLER_H
