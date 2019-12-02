/**
 * @file 
 * @author Basil Rommens
 * @date 30/11/2019
 * @brief ...
 */

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <iostream>
#include <list>

int main(int argc, char** argv)
{


    /*
    sf::Event event;

    // If true, you will continue to receive keyboard events when a key is held down
    // If false, it will only fire one event per press until released
    renderWindow.setKeyRepeatEnabled(false);

    std::unordered_map<int, bool> keys;
    std::list<int> changedKeys;

    while (renderWindow.isOpen()) {
        changedKeys.clear();

        while (renderWindow.pollEvent(event)) {
            if (event.type==sf::Event::EventType::Closed)
                renderWindow.close();

            if (event.type==sf::Event::EventType::KeyPressed) {
                if (keys.count(event.key.code)==0) {
                    keys[event.key.code] = true;
                    changedKeys.push_back(event.key.code);
                }
            }
            if (event.type==sf::Event::EventType::KeyReleased) {
                if (keys.count(event.key.code)==1) {
                    keys.erase(event.key.code);
                    changedKeys.push_back(event.key.code);
                }
            }
        }

        std::cout << "Currently pressed keys: ";

        // To get the actual value as a string, you need to use Thor or write your own version
        for (auto& keyValue : keys)
            std::cout << keyValue.first << " ";
        std::cout << std::endl;

        if (!changedKeys.empty()) {
            std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Keys changed" << std::endl;
        }
        renderWindow.clear();
        renderWindow.display();
    }
    */
}