/**
 * @file Controller.cpp
 * @author Basil Rommens
 * @date 12/17/19
 * @brief The cpp file of the class Controller
 */
#include "Controller.h"

void Controller::run(sf::RenderWindow& window, EntityNS::World& world)
{
    // notify the world that it needs to check all the collision
    notify(nullptr, Utils::Event::CHECK_COLLISIONS);

    // TODO find something that can change input controls
    notify(nullptr, Utils::Event::UNMOVE); // Make all the enemy ships movable

    // Update the position of all the bullets
    for (auto entity: world.getEntities()) {
        if (entity->getType()=="bullet") {
            // If it is already being observed by the controller class do nothing
            if (not entity->isInControl()) {
                this->addObserver(entity);
                entity->setInControl();
            }
            notify(entity, Utils::Event::UPDATE_DRAW);
        }
    }

    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    std::shared_ptr<EntityNS::Entity> player = world.getPlayer();
    while (window.pollEvent(event)) {
        // "close requested" event: we close the window
        if (event.type==sf::Event::Closed) {
            notify(nullptr, Utils::Event::CLOSE_WINDOW);
            break;
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
                break;
            }
        }
    }

    // Move all the enemy ships
    notify(nullptr, Utils::Event::MOVE);
    // Decrease the player/enemy firing delay with 1 every frame
    notify(nullptr, Utils::Event::DECREASE_DELAY);
}