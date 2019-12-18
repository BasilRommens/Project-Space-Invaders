/**
 * @file 
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief ...
 */

#include "Position.h"

// TODO remove duplication from moveXPos and moveYPos

Utils::Position::Position(double x_pos, double y_pos)
        :xPos(x_pos), yPos(y_pos) { }

void Utils::Position::moveXPos(double x_pos, double distance)
{
    // Set the new possible x position
    double newXPos = x_pos+distance;

    // TODO throw an error when out of bounds
    if (newXPos>CoordinateBound::UPPER_X) {
        xPos = CoordinateBound::UPPER_X;
    }
    else if (newXPos<CoordinateBound::LOWER_X) {
        xPos = CoordinateBound::LOWER_X;
    }
    else {
        xPos = newXPos;
    }
}

void Utils::Position::moveYPos(double y_pos, double distance)
{
    // Set the new possible y position
    double newXPos = y_pos+distance;

    // TODO throw an error when out of bounds
    if (newXPos>CoordinateBound::UPPER_Y) {
        xPos = CoordinateBound::UPPER_Y;
    }
    else if (newXPos<CoordinateBound::LOWER_Y) {
        xPos = CoordinateBound::LOWER_Y;
    }
    else {
        xPos = newXPos;
    }
}
