/**
 * @file 
 * @author Basil Rommens
 * @date 02/12/2019
 * @brief ...
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
                std::cout << (char) event.key.code << std::endl;
            }
        }
        renderWindow.clear();
        renderWindow.draw(sprite);
        renderWindow.display();
    }
}

void mainKeyboard()
{
    while (true) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
            std::cout << "K" << std::endl;
        }
        usleep(100000);
    }
}

int main()
{
    draw();
    return 0;
}