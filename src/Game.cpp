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

void Game::load(const std::string& level)
{

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
