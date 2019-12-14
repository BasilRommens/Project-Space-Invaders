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

int main()
{
    std::shared_ptr<Utils::Transformation> a = Utils::Transformation::getTransformation();
    std::shared_ptr<Utils::Transformation> b = Utils::Transformation::getTransformation();
    std::shared_ptr<Utils::Stopwatch> s = Utils::Stopwatch::getStopwatch();
    std::shared_ptr<Utils::Stopwatch> t = Utils::Stopwatch::getStopwatch();

    std::cout << a << "=" << b << std::endl;
    std::cout << s << "=" << t << std::endl;

    if (&a==&b) {
        std::cout << "Singleton pattern working for Transformation" << std::endl;
    }
    if (&s==&t) {
        std::cout << "Singleton pattern working for Stopwatch" << std::endl;
    }

    // TODO figuring out how keyboard inputs can change the location of the player
    return 0;
}