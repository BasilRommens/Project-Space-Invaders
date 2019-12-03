/**
 * @file 
 * @author Basil Rommens
 * @date 02/12/2019
 * @brief ...
 */

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <list>

int main()
{
    sf::Texture texture;
    texture.loadFromFile("img/alien.png");

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::RenderWindow renderWindow(sf::VideoMode(800, 800), "SFML Demo");

    // run the program as long as the window is open
    while (renderWindow.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (renderWindow.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type==sf::Event::Closed) {
                renderWindow.close();
            }
        }
        renderWindow.clear();
        renderWindow.draw(sprite);
        renderWindow.display();
    }

    // TODO figuring out how keyboard inputs can change the location of the player
    return 0;
}
