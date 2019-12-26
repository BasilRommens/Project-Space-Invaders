/**
 * @file testMain.cpp
 * @author Basil Rommens
 * @date 02/12/2019
 * @brief The cpp file of the main that does all the testing
 */

#include <SFML/Graphics.hpp>
#include "utils/Transformation.h"
#include "utils/Stopwatch.h"
#include <unordered_map>
#include <iostream>
#include <list>
#include <memory>
#include <zconf.h>

void draw()
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
                    std::cout << "left" << std::endl;
                }
                else if (event.key.code==sf::Keyboard::D) {
                    sprite.move(sf::Vector2f(4, 0));
                    std::cout << "right" << std::endl;
                }
                else if (event.key.code==sf::Keyboard::Space) {
                    std::cout << "space" << std::endl;
                }
                else if (event.key.code==sf::Keyboard::Escape) {
                    std::cout << "close" << std::endl;
                    renderWindow.close();
                }
            }
        }
        renderWindow.clear();
        renderWindow.draw(sprite);
        renderWindow.display();
    }
}

int main()
{
    draw();
    return 0;
}