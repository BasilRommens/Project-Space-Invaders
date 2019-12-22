/**
 * @file Position.cpp
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The cpp file of the class Position
 */

#include "Position.h"

// TODO remove duplication from moveXPos and moveYPos

Utils::Position::Position(double x_pos, double y_pos)
        :xPos(x_pos), yPos(y_pos) { }

void Utils::Position::moveXPos(double distance)
{
    // Set the new possible x position
    double newXPos = xPos+distance;

    // TODO throw an error when out of bounds
    if (newXPos>CoordinateBound::UPPER_X) {
        std::cout << "hit upper bounds" << std::endl;
        xPos = CoordinateBound::UPPER_X;
    }
    else if (newXPos<CoordinateBound::LOWER_X) {
        std::cout << "hit lower bounds" << std::endl;
        xPos = CoordinateBound::LOWER_X;
    }
    else {
        xPos = newXPos;
    }
}

void Utils::Position::moveYPos(double distance)
{
    // Set the new possible y position
    double newYPos = yPos+distance;

    // TODO throw an error when out of bounds
    if (newYPos>CoordinateBound::UPPER_Y) {
        yPos = CoordinateBound::UPPER_Y;
    }
    else if (newYPos<CoordinateBound::LOWER_Y) {
        yPos = CoordinateBound::LOWER_Y;
    }
    else {
        yPos = newYPos;
    }
}

Utils::Position::Position() { }

double Utils::Position::getXPos() const
{
    return xPos;
}

double Utils::Position::getYPos() const
{
    return yPos;
}
