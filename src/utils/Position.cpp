/**
 * @file Position.cpp
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The cpp file of the class Position
 */

#include "Position.h"

// TODO remove duplication from moveXPos and moveYPos

Utils::Position::Position(double x, double y) : x(x), y(y) {}

void Utils::Position::moveXPos(double distance, const Hitbox hitbox)
{
        // Set the new possible x position
        double newXPos = x + distance;

        // TODO throw an error when out of bounds
        if (newXPos + hitbox.getWidth() > CoordinateBound::UPPER_X) {
                x = CoordinateBound::UPPER_X - hitbox.getWidth();
                throw std::out_of_range("The entity tried to get out of range");
        } else if (newXPos < CoordinateBound::LOWER_X) {
                x = CoordinateBound::LOWER_X;
                throw std::out_of_range("The entity tried to get out of range");
        } else {
                x = newXPos;
        }
}

void Utils::Position::moveYPos(double distance, const Hitbox hitbox)
{
        // Set the new possible y position
        double newYPos = y + distance;

        if (newYPos > CoordinateBound::UPPER_Y) {
                y = CoordinateBound::UPPER_Y;
                throw std::out_of_range("The entity tried to get out of range");
        } else if (newYPos - hitbox.getHeight() < CoordinateBound::LOWER_Y) {
                y = CoordinateBound::LOWER_Y + hitbox.getHeight();
                throw std::out_of_range("The entity tried to get out of range");
        } else {
                y = newYPos;
        }
}

Utils::Position::Position() {}

double Utils::Position::getX() const { return x; }

double Utils::Position::getY() const { return y; }

void Utils::Position::setPosition(Utils::Position newPos) { *this = newPos; }
