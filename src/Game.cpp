/**
 * @file 
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief ...
 */

#include "Game.h"

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
        // Display failure message
    }
}

// TODO error on empty filename
void Game::load(const std::string& level)
{
    json j(level);
    loadPlayer(j["Player"]);
    loadEnemy(j["Enemies"]);
}

bool Game::play()
{
    sf::Texture texture;
    texture.loadFromFile("img/laser.png");

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "SFML Demo");
    sprite.setOrigin(-29, -(renderWindow.getSize().x/2.0));

    Controller control;

    // run the program as long as the window is open
    while (renderWindow.isOpen()) {
        /// Part of control
        control.run(renderWindow);

        /// Part of view
        renderWindow.clear();
        renderWindow.draw(sprite);
        renderWindow.display();
    }
}

// TODO error on empty filename
void Game::loadPlayer(const std::string& player)
{
    json j(player);

    // TODO if type is a mismatch -> error
    std::string image = j["Image"];
    Utils::Position position(j["xPos"], j["yPos"]);
    double HP = j["HP"];
    double HSpeed = j["HSpeed"];
    double damage = j["Damage"];

    std::shared_ptr<Entity> playerShip(new PlayerShip(image, position, HP, HSpeed, damage));
}

// TODO error on empty filename
void Game::loadEnemy(const std::string& enemy)
{
    json j(enemy);

    // TODO if type is a mismatch -> error
    std::string image = j["Image"];
    Utils::Position position(j["xPos"], j["yPos"]);
    double HP = j["HP"];
    double HSpeed = j["HSpeed"];
    double VSpeed = j["VSpeed"];
    double damage = j["Damage"];

    std::shared_ptr<Entity> enemyShip(new EnemyShip(image, position, HP, HSpeed, damage, VSpeed));
}
