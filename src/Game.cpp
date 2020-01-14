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

void Game::start(const std::vector<std::string>& levels)
{
    sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Project Space Invaders");

    // TODO causes error because it probably is a member variable :( FIX
    std::shared_ptr<ObserverPattern::Observer> sharedWorld(&world);

    bool failure{};

    for (const auto& level: levels) {
        load(level);
        failure = play(renderWindow, sharedWorld);
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
}

bool Game::play(sf::RenderWindow& renderWindow, std::shared_ptr<ObserverPattern::Observer> sharedWorld)
{
    bool failure = false;

    std::shared_ptr<sf::RenderWindow> window(&renderWindow);
    std::shared_ptr<View::Draw> draw(new View::Draw(window, world));
    std::shared_ptr<ObserverPattern::Observer> drawShared(draw);

    // add draw object to the world because it enables to spawn bullets
    world.addObserver(drawShared);

    // Add the the observer to each of the dummy bullets of the players/enemies
    for (auto entity: world.getEntities()) {
        if (entity->getType()=="enemy" or entity->getType()=="player") {
            std::shared_ptr<Model::Bullet> bullet = entity->getDummyBullet();
            bullet->addObserver(drawShared);
        }
    }

    // Add the draw object to each class
    for (const auto entity: world.getEntities()) {
        entity->addObserver(drawShared);
    }

    // Add the world to the controller for observation in order to apply collision detection
    controller.addObserver(sharedWorld);

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
        if (not world.hasPlayer()) {
            failure = true;
            break;
        }
        // if there are no enemies left in space
        if (not world.hasEnemies()) {
            break;
        }
        draw->view();

        wait();
    }

    world.reset();
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
    Utils::Hitbox hitbox(j["Hitbox"]["Width"], j["Hitbox"]["Height"]);

    std::shared_ptr<Model::Entity> playerShip(
            new Model::PlayerShip(image, position, HP, HSpeed, 20, hitbox, world));
    playerShip->addBullet(createBullet(j["Bullet"], playerShip));
    world.addEntity(playerShip);

    //playerShip->addWorld(world);

    std::shared_ptr<ObserverPattern::Observer> observerPlayer(playerShip);
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

        Utils::Hitbox hitbox{ship["Hitbox"]["Width"], ship["Hitbox"]["Height"]};

        auto enemyShip = std::make_shared<Model::EnemyShip>(
                Model::EnemyShip(image, position, HP, HSpeed, 30, hitbox, VSpeed, world));

        enemyShip->addBullet(createBullet(ship["Bullet"], enemyShip));

        std::shared_ptr<Model::Entity> sharedEntity(enemyShip);
        world.addEntity(sharedEntity);

        std::shared_ptr<ObserverPattern::Observer> sharedObserver(enemyShip);
        controller.addObserver(sharedObserver);

        std::weak_ptr<Model::EnemyShip> weakEnemy = enemyShip;
        enemyShip->addShip(weakEnemy);

        //enemyShip->addWorld(world);
    }
}

void Game::loadWorld(const std::string& worldName)
{
    // Parse json file
    std::ifstream i(worldName);
    json j;
    i >> j;

    world = Model::World(j["Image"], j["End"]);
}

std::shared_ptr<Model::Bullet>
Game::createBullet(const std::string& fileName, std::weak_ptr<Model::Entity> entity)
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
    Utils::Hitbox hitbox{j["Hitbox"]["Width"], j["Hitbox"]["Height"]};
    // Move the bullet so that it is centred over the entity
    position.moveXPos(-hitbox.getWidth()/2, hitbox);
    Utils::Direction direction{};
    // TODO fix y spawning
    if (entity.lock()->getType()=="enemy") {
        direction = Utils::Direction::DOWN;
        position.moveYPos(-entity.lock()->getHitbox().getHeight(), hitbox);
    }
    else if (entity.lock()->getType()=="player") {
        direction = Utils::Direction::UP;
        position.moveYPos(hitbox.getHeight(), hitbox);
    }
    return std::make_shared<Model::Bullet>(
            Model::Bullet(image, direction, speed, damage, position, entity, hitbox));
}

void Game::displayLost(sf::RenderWindow& renderWindow)
{
    sf::Text text;

    sf::Font font;

    // TODO throw exception
    if (!font.loadFromFile("input/Roboto/Roboto-Black.ttf")) {
        std::cout << "failed to load font" << std::endl;
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
