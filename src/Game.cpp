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

void Game::load(std::string level)
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

    // run the program as long as the window is open
    while (renderWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (renderWindow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type==sf::Event::Closed) {
                renderWindow.close();
            }
            if (event.type==sf::Event::KeyPressed) {
                if (event.key.code==sf::Keyboard::A) {
                    sprite.move(sf::Vector2f(-4, 0));
                }
                else if (event.key.code==sf::Keyboard::D) {
                    sprite.move(sf::Vector2f(4, 0));
                }
                else if (event.key.code==sf::Keyboard::Space) {
                    std::cout << "space" << std::endl;
                }
                else if (event.key.code==sf::Keyboard::Escape) {
                    renderWindow.close();
                }
            }
        }
        renderWindow.clear();
        renderWindow.draw(sprite);
        renderWindow.display();
    }
}
