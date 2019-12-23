/**
 * @file Position.cpp
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The cpp file of the class Position
 */

#include "Position.h"

// TODO remove duplication from moveXPos and moveYPos

Utils::Position::Position(double x, double y)
        :x(x), y(y) { }

void Utils::Position::moveXPos(double distance)
{
    // Set the new possible x position
    double newXPos = x+distance;

    // TODO throw an error when out of bounds
    if (newXPos>CoordinateBound::UPPER_X) {
        std::cout << "hit upper bounds" << std::endl;
        x = CoordinateBound::UPPER_X;
    }
    else if (newXPos<CoordinateBound::LOWER_X) {
        std::cout << "hit lower bounds" << std::endl;
        x = CoordinateBound::LOWER_X;
    }
    else {
        x = newXPos;
    }
}

void Utils::Position::moveYPos(double distance)
{
    // Set the new possible y position
    double newYPos = y+distance;

    // TODO throw an error when out of bounds
    if (newYPos>CoordinateBound::UPPER_Y) {
        y = CoordinateBound::UPPER_Y;
    }
    else if (newYPos<CoordinateBound::LOWER_Y) {
        y = CoordinateBound::LOWER_Y;
    }
    else {
        y = newYPos;
    }
}

Utils::Position::Position() { }

double Utils::Position::getX() const
{
    return x;
}

double Utils::Position::getY() const
{
    return y;
}

void Utils::Position::setPosition(Utils::Position newPos)
{
    *this = newPos;
}
