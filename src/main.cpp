/**
 * @file main.cpp
 * @author Basil Rommens
 * @date 30/11/2019
 * @brief The place from where all the code is run
 */

#include "Game.h"

double EntityNS::EnemyShip::distance = 0.f;
std::vector<std::weak_ptr<EntityNS::EnemyShip>> EntityNS::EnemyShip::otherShips = {};

int main(int argc, char** argv)
{
    Game g;
    std::vector<std::string> levels{argv[1]};
    g.start(levels);
}