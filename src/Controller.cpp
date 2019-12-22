/**
 * @file Controller.cpp
 * @author Basil Rommens
 * @date 12/17/19
 * @brief The cpp file of the class Controller
 */
#include "Controller.h"

void Controller::run(sf::RenderWindow& window, World& world)
{
    // TODO find something that can change input controls

    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    std::shared_ptr<Entity> player = world.getPlayer();
    while (window.pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type==sf::Event::Closed) {
            notify(nullptr, Utils::Event::CLOSE_WINDOW);
        }
        if (event.type==sf::Event::KeyPressed) {
            if (event.key.code==sf::Keyboard::A) {
                notify(player, Utils::Event::MOVE_LEFT);
            }
            else if (event.key.code==sf::Keyboard::D) {
                notify(player, Utils::Event::MOVE_RIGHT);
            }
            else if (event.key.code==sf::Keyboard::Space) {
                notify(player, Utils::Event::FIRE_BULLET);
            }
            else if (event.key.code==sf::Keyboard::Escape) {
                notify(nullptr, Utils::Event::CLOSE_WINDOW);
            }
        }
    }
}

void Controller::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    if (entity) {

    }
}
