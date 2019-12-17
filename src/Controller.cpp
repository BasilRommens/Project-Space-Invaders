/**
 * @file Controller.cpp
 * @author Basil Rommens
 * @date 12/17/19
 * @brief The cpp file of the class Controller
 */
#include "Controller.h"

void Controller::run(sf::RenderWindow& window)
{
    // TODO find something that can change input controls

    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event{};
    while (window.pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type==sf::Event::Closed) {
            notify(Utils::Event::CLOSE_WINDOW);
        }
        if (event.type==sf::Event::KeyPressed) {
            if (event.key.code==sf::Keyboard::A) {
                notify(Utils::Event::MOVE_LEFT);
            }
            else if (event.key.code==sf::Keyboard::D) {
                notify(Utils::Event::MOVE_RIGHT);
            }
            else if (event.key.code==sf::Keyboard::Space) {
                notify(Utils::Event::FIRE_BULLET);
            }
            else if (event.key.code==sf::Keyboard::Escape) {
                notify(Utils::Event::CLOSE_WINDOW);
            }
        }
    }
}
