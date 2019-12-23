/**
 * @file Controller.cpp
 * @author Basil Rommens
 * @date 12/17/19
 * @brief The cpp file of the class Controller
 */
#include "Controller.h"

void Controller::run(sf::RenderWindow& window, EntityNS::World& world)
{
    // TODO find something that can change input controls

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
}

void Controller::onNotify(std::shared_ptr<EntityNS::Entity> entity, Utils::Event event)
{
    if (entity) {

    }
}

void Controller::update(std::shared_ptr<EntityNS::Entity> entity)
{

}
