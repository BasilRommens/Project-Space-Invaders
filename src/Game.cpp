/**
 * @file Game.cpp
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The cpp file of the class Game
 */

#include "Game.h"

// set the instance of the Stopwatch to nullptr to be not pointing to anything
std::shared_ptr<Utils::Stopwatch> Utils::Stopwatch::instance = nullptr;

Game::Game() { }

void Game::start(std::vector<std::string> levels)
{
    sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Project Space Invaders");
    bool failure{};

    for (auto level: levels) {
        load(level);
        failure = play(renderWindow);
        if (failure) {
            break;
        }
        if (not renderWindow.isOpen()) {
            break;
        }
    }

    if (failure) {
        // TODO Display failure message
    }
}

bool Game::play(sf::RenderWindow& renderWindow)
{
    // TODO add the visualization of the world and all its entities
    std::shared_ptr<sf::RenderWindow> window(&renderWindow);
    std::shared_ptr<Draw> draw(new Draw(window, world));
    std::shared_ptr<Observer> drawShared(draw);

    // Add the draw object to each class
    for (auto& entity: world.getEntities()) {
        entity->addObserver(drawShared);
    }

    // run the program as long as the window is open
    while (renderWindow.isOpen()) {
        // start the timing of the stopwatch
        stopwatch->start();

        /// Part of control
        controller.run(renderWindow, world);

        /// Part of view
        draw->view();\

        wait();
    }

    return false;
}

// TODO error on empty filename
void Game::load(const std::string& level)
{
    // Parse json file
    std::ifstream i(level);
    json j;
    i >> j;

    loadWorld(j["World"]);
    loadPlayer(j["Player"]);
    loadEnemy(j["Enemies"]);

    // TODO add check for when entity is not a valid pointer
    // Add observers to the controller of the game
    for (auto entity: world.getEntities()) {
        controller.addObserver(entity);
    }
}

// TODO error on empty filename
void Game::loadPlayer(const std::string&& player)
{
    // Parse json file
    std::ifstream i(player);
    json j;
    i >> j;

    // TODO if type is a mismatch -> error
    std::string image = j["Image"];
    Utils::Position position(j["xPos"], j["yPos"]);
    double HP = j["HP"];
    double HSpeed = j["HSpeed"];
    double damage = j["Damage"];

    std::shared_ptr<Entity> playerShip(new PlayerShip(image, position, HP, HSpeed, damage));
    world.addEntity(playerShip);
    playerShip->addObserver(std::make_shared<Entity>(world));
}

// TODO error on empty filename
void Game::loadEnemy(const std::string&& enemy)
{
    // Parse json file
    std::ifstream i(enemy);
    json j;
    i >> j;

    // TODO if type is a mismatch -> error
    for (auto ship: j["Ships"]) {
        std::string image = ship["Image"];
        Utils::Position position(ship["xPos"], ship["yPos"]);
        double HP = ship["HP"];
        double HSpeed = ship["HSpeed"];
        double VSpeed = ship["VSpeed"];
        double damage = ship["Damage"];

        std::shared_ptr<Entity> enemyShip(new EnemyShip(image, position, HP, HSpeed, damage, VSpeed));
        world.addEntity(enemyShip);
        std::shared_ptr<Entity> sharedWorld(&world);
        enemyShip->addObserver(sharedWorld);
    }
}

void Game::loadWorld(const std::string&& worldName)
{
    world = World(worldName);
}

void Game::wait()
{
    int elapsedTime = stopwatch->get_lap().count()*1000000;
    if (elapsedTime<Utils::frameDuration) {
        // multiplied by 100 cause framerate doesnt seem right
        usleep(Utils::frameDuration-elapsedTime);
    }
}


