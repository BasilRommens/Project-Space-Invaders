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

int main(int argc, char** argv)
{
    Game g;
    std::vector<std::string> levels{argv[1]};
    g.start(levels);
}