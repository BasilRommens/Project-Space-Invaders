/**
 * @file Controller.h
 * @author Basil Rommens
 * @date 12/17/19
 * @brief The header file of the class Controller
 */

#ifndef PROJECT_SPACE_INVADERS_CONTROLLER_H
#define PROJECT_SPACE_INVADERS_CONTROLLER_H

#include <SFML/Graphics.hpp>

#include "Subject.h"
#include "Observer.h"

class Controller : public Subject {
public:
    void run(sf::RenderWindow& window);
};

#endif //PROJECT_SPACE_INVADERS_CONTROLLER_H
