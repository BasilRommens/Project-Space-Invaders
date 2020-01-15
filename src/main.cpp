/**
 * @file main.cpp
 * @author Basil Rommens
 * @date 30/11/2019
 * @brief The place from where all the code is run
 */

#include "Game.h"
#include "GameParser.h"
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

int main(int argc, char** argv)
{
    try {
        Game g;
        GameParser gameParser{g};
        std::vector<std::string> levels = gameParser.parseGame(argv[1]);

        // Start the game
        g.start(levels);
    }
        // https://nlohmann.github.io/json/classnlohmann_1_1basic__json_a9a0aced019cb1d65bb49703406c84970.html (consulted on 14/01/2020)
    catch (json::exception& e) {
        if (e.id==101) {
            std::cerr << "The path to your json file is probably wrong" << std::endl
                      << "or your json file is faulty" << std::endl;
        }
    }
}