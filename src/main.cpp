/**
 * @file 
 * @author Basil Rommens
 * @date 30/11/2019
 * @brief ...
 */

#include "Game.h"

int main(int argc, char** argv)
{
    Game g;
    g.start(std::vector<std::string>{"input/level1.json"});
}