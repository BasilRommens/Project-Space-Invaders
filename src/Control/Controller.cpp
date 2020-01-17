/**
 * @file Controller.cpp
 * @author Basil Rommens
 * @date 12/17/19
 * @brief The cpp file of the class Controller
 */
#include "Controller.h"

void Control::Controller::run(sf::RenderWindow& window, std::shared_ptr<Model::World> world)
{
        // notify the world that it needs to check all the collision
        notify(nullptr, Utils::Event::CHECK_COLLISIONS);

        // TODO find something that can change input controls
        notify(nullptr, Utils::Event::UNMOVE); // Make all the enemy ships movable

        // Update the position of all the bullets
        for (std::shared_ptr<Model::Entity> entity : world->getEntities()) {
                if (entity->getType() == "bullet") {
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
        std::shared_ptr<Model::Entity> player = world->getPlayer();
        while (window.pollEvent(event)) {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed) {
                        notify(nullptr, Utils::Event::CLOSE_WINDOW);
                        break;
                }
                if (event.type == sf::Event::KeyPressed) {
                        if (event.key.code == sf::Keyboard::A) {
                                notify(player, Utils::Event::MOVE_LEFT);
                        } else if (event.key.code == sf::Keyboard::D) {
                                notify(player, Utils::Event::MOVE_RIGHT);
                        } else if (event.key.code == sf::Keyboard::Space) {
                                notify(player, Utils::Event::FIRE_BULLET);
                        } else if (event.key.code == sf::Keyboard::Escape) {
                                notify(nullptr, Utils::Event::CLOSE_WINDOW);
                                break;
                        }
                }
        }
        // Remove all the objects that we can't observe in the controller
        // We do this by checking for all the observers if they are still in the world
        removeUnnecessaryObservers(world);

        // Move all the enemy ships
        notify(nullptr, Utils::Event::MOVE);
        // Decrease the player/enemy firing delay with 1 every frame
        notify(nullptr, Utils::Event::DECREASE_DELAY);
}

void Control::Controller::removeUnnecessaryObservers(std::shared_ptr<Model::World> world)
{
    for (std::shared_ptr<ObserverPattern::Observer> observer : this->getObservers()) {
        // Do not proceed checking if the observer is the world itself
        if (observer.get() == world.get()) {
            continue;
        }
        // If the observer is a nullpointer just continue to the next one
        if (not observer) {
            continue;
        }
        bool found = false;
        for (std::shared_ptr<Model::Entity> entity : world->getEntities()) {
            if (observer == entity) {
                found = true;
                break;
            }
        }
        // If we did not find it in the world then we can delete it
        if (not found) {
            if (observer->getType() == "enemy") {
                std::shared_ptr<Model::Entity> entity =
                        std::static_pointer_cast<Model::Entity>(observer);
                entity->removeThis();
                entity->clearObservers();
            }
            this->removeObserver(observer);
        }
    }
}
