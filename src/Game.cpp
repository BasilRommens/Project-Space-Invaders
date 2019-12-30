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

    // add draw object to the world because it enables to spawn bullets
    world.addObserver(drawShared);

    // Add the draw object to each class
    for (const auto entity: world.getEntities()) {
        entity->addObserver(drawShared);
    }

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
        draw->view();

        wait();
    }

    return false;
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

// TODO error on empty filename
void Game::load(const std::string& level)
{
    // Parse json file
    std::ifstream i(level);
    json j;
    i >> j;

    // TODO make extra functions for applying the observer pattern
    loadWorld(j["World"]);
    loadPlayer(j["Player"]);
    loadEnemy(j["Enemies"]);

    // TODO add check for when entity is not a valid pointer
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
    Hitbox hitbox(j["Hitbox"]["Width"], j["Hitbox"]["Height"]);

    std::shared_ptr<EntityNS::Entity> playerShip(
            new EntityNS::PlayerShip(image, position, HP, HSpeed, 20, hitbox));
    playerShip->addBullet(createBullet(j["Bullet"], playerShip));
    world.addEntity(playerShip);

    std::shared_ptr<Observer> sharedWorld(&world);
    playerShip->addObserver(sharedWorld);

    std::shared_ptr<Observer> observerPlayer(playerShip);
    controller.addObserver(observerPlayer);
}

// TODO error on empty filename
void Game::loadEnemy(const std::string&& enemy)
{
    // Parse json file
    std::ifstream i(enemy);
    json j;
    i >> j;

    double HSpeed = j["HSpeed"];
    double VSpeed = j["VSpeed"];

    // TODO if type is a mismatch -> error
    for (auto ship: j["Ships"]) {
        std::string image = ship["Image"];
        Utils::Position position(ship["xPos"], ship["yPos"]);
        double HP = ship["HP"];

        Hitbox hitbox{ship["Hitbox"]["Width"], ship["Hitbox"]["Height"]};

        auto enemyShip = std::make_shared<EntityNS::EnemyShip>(
                EntityNS::EnemyShip(image, position, HP, HSpeed, 30, hitbox, VSpeed));

        enemyShip->addBullet(createBullet(ship["Bullet"], enemyShip));

        std::shared_ptr<EntityNS::Entity> sharedEntity(enemyShip);
        world.addEntity(sharedEntity);

        std::shared_ptr<Observer> sharedObserver(enemyShip);
        controller.addObserver(sharedObserver);

        std::shared_ptr<Observer> sharedWorld(&world);
        enemyShip->addObserver(sharedWorld);

        std::weak_ptr<EntityNS::EnemyShip> weakEnemy = enemyShip;
        enemyShip->addShip(weakEnemy);
    }
}

void Game::loadWorld(const std::string&& worldName)
{
    world = EntityNS::World(worldName);
}

std::shared_ptr<EntityNS::Bullet> Game::createBullet(std::string fileName, std::weak_ptr<EntityNS::Entity> entity)
{
    // Parse json file
    std::ifstream i(fileName);
    json j;
    i >> j;

    Utils::Position position(entity.lock()->getHitbox().getWidth()/2, 0);
    std::string image = j["Image"];
    double damage = j["Damage"];
    double speed = j["Speed"];
    // TODO Clean up this mess
    Hitbox hitbox{j["Hitbox"]["Width"], j["Hitbox"]["Height"]};
    // Move the bullet so that it is centred over the entity
    position.moveXPos(-hitbox.getWidth()/2);
    Utils::Direction direction;
    if (entity.lock()->getType()=="enemy") {
        direction = Utils::Direction::DOWN;
        position.moveYPos(hitbox.getHeight());

    }
    else if (entity.lock()->getType()=="player") {
        direction = Utils::Direction::UP;
        position.moveYPos(-entity.lock()->getHitbox().getHeight());
    }

    return std::make_shared<EntityNS::Bullet>(
            EntityNS::Bullet(image, direction, speed, damage, position, entity, hitbox));
}
