/**
 * @file 
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief ...
 */

#include "Game.h"

Game::Game() { }

void Game::start(std::vector<std::string> levels)
{
    bool failure{};
    for (auto level: levels) {
        load(level);
        failure = play();
        if (failure) {
            break;
        }
    }

    if (failure) {
        // TODO Display failure message
    }
}

bool Game::play()
{
    sf::Texture texture;
    texture.loadFromFile("img/laser.png");

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "SFML Demo");
    sprite.setOrigin(-29, -(renderWindow.getSize().x/2.0));

    // run the program as long as the window is open
    while (renderWindow.isOpen()) {
        /// Part of control
        controller.run(renderWindow);

        /// Part of view
        renderWindow.clear();
        renderWindow.draw(sprite);
        renderWindow.display();
    }

    return true;
}

// TODO error on empty filename
void Game::load(const std::string& level)
{
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
}

// TODO error on empty filename
void Game::loadEnemy(const std::string&& enemy)
{
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
    }
}

void Game::loadWorld(const std::string&& worldName)
{
    world = World(worldName);
}


