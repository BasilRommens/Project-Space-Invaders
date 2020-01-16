/**
 * @file Game.cpp
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The cpp file of the class Game
 */

#include "Game.h"
#include "GameParser.h"

// set the instance of the Stopwatch to nullptr to be not pointing to anything
std::shared_ptr<Utils::Stopwatch> Utils::Stopwatch::instance = nullptr;

Game::Game() { }

void Game::start(const std::vector<std::string>& levels)
{
    sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Project Space Invaders");

    // TODO causes error because it probably is a member variable :( FIX

    bool failure{};

    GameParser gameParser{*this};
    for (const auto& level: levels) {
        // Parse the level and then set all the parsed elements on the current game
        gameParser.parseLevel(level);

        failure = play(renderWindow);
        if (failure) {
            break;
        }
        if (not renderWindow.isOpen()) {
            break;
        }
    }

    // TODO try to do this inside loop to restart game
    if (failure and renderWindow.isOpen()) {
        displayLost(renderWindow);
    }

    // Downcast worldObserver
    std::shared_ptr<Model::World> world = std::static_pointer_cast<Model::World>(worldObserver);

    this->controller.clearObservers();
}

bool Game::play(sf::RenderWindow& renderWindow)
{
    bool failure = false;

    // Downcast worldObserver
    std::shared_ptr<Model::World> world = std::static_pointer_cast<Model::World>(worldObserver);

    std::shared_ptr<sf::RenderWindow> window(&renderWindow);
    std::shared_ptr<View::Draw> draw(new View::Draw(window, world));
    std::shared_ptr<ObserverPattern::Observer> drawShared(draw);

    // add draw object to the worldObserver because it enables to spawn bullets
    world->addObserver(drawShared);

    // Add the the observer to each of the dummy bullets of the players/enemies
    for (auto entity: world->getEntities()) {
        if (entity->getType()=="enemy" or entity->getType()=="player") {
            std::shared_ptr<Model::Bullet> bullet = entity->getDummyBullet();
            bullet->addObserver(drawShared);
        }
    }

    // Add the draw object to each class
    for (const auto entity: world->getEntities()) {
        entity->addObserver(drawShared);
    }

    // Add the worldObserver to the controller for observation in order to apply collision detection
    controller.addObserver(worldObserver);

    // run the program as long as the window is open
    while (renderWindow.isOpen()) {
        // start the timing of the stopwatch
        stopwatch->start();

        /// Part of control
        controller.run(renderWindow, world);

        /// Part of view
        // if the window has been closed then exit the level
        if (not draw->isOpen()) {
            break;
        }
        // if the player has been destroyed
        if (not world->hasPlayer()) {
            failure = true;
            break;
        }
        // if there are no enemies left in space
        if (not world->hasEnemies()) {
            break;
        }
        draw->view();

        wait();
    }

    worldObserver.reset();
    controller.clearObservers();
    return failure;
}

void Game::wait()
{
    // TODO remove the 1000000.f because its ugly
    int elapsedTime = stopwatch->get_lap().count()*1000000.f;
    if (elapsedTime<Utils::frameDuration) {
        // multiplied by 100 cause framerate doesnt seem right
        usleep(Utils::frameDuration-elapsedTime);
    }
}

void Game::displayLost(sf::RenderWindow& renderWindow)
{
    sf::Text text;

    sf::Font font;

    if (!font.loadFromFile("input/Roboto/Roboto-Black.ttf")) {
        throw std::domain_error("failed to load font");
    }

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("Game over");

    // set the character size
    text.setCharacterSize(60); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);
    text.setPosition(renderWindow.getPosition().x/2-text.getGlobalBounds().width/4, 0);

    renderWindow.draw(text);
    renderWindow.display();
    while (true) { }
}