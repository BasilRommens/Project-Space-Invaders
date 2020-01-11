/**
 * @file main.cpp
 * @author Basil Rommens
 * @date 30/11/2019
 * @brief The place from where all the code is run
 */

#include "Game.h"
#include "Model/EnemyShip.h"

double Model::EnemyShip::distance = 0.f;

std::vector<std::weak_ptr<Model::EnemyShip>> Model::EnemyShip::otherShips = {};

void Model::EnemyShip::removeThis()
{
    for (auto otherShipIt = otherShips.begin(); otherShipIt!=otherShips.end(); ++otherShipIt) {
        if (otherShipIt->lock().get()==this) {
            otherShips.erase(otherShipIt);
            break;
        }
    }
}

// TODO add exception handling if wrong filetype
int main(int argc, char** argv)
{
    try {
        // Parse json file of the game
        std::ifstream i(argv[1]);
        json j;
        i >> j;

        // add all the levels from the game json to the levels vector
        std::vector<std::string> levels{};
        for (auto levelFile: j["Levels"]) {
            levels.push_back(levelFile);
        }

        // Start the game
        Game g;
        g.start(levels);
    }
    catch (...) {
        std::cout << ":(" << std::endl;
    }
}