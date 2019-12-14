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

void draw()
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
}

#include <iostream>

using namespace std;

class Singleton {
    static Singleton* instance;
    int data;

    // Private constructor so that no objects can be created.
    Singleton()
    {
        data = 0;
    }

public:
    static Singleton* getInstance()
    {
        if (!instance)
            instance = new Singleton;
        return instance;
    }

    int getData()
    {
        return this->data;
    }

    void setData(int data)
    {
        this->data = data;
    }
};

//Initialize pointer to zero so that it can be initialized in first call to getInstance

int main()
{
    Transformation a = Transformation::getTransformation();

    // TODO figuring out how keyboard inputs can change the location of the player
    return 0;
}
