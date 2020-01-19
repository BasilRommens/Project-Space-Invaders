/**
 * @file Position.cpp
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The cpp file of the class Position
 */

#include "Position.h"

// TODO remove duplication from moveXPos and moveYPos

Utils::Position::Position(double x, double y)
{
        if (x < CoordinateBound::LOWER_X or x > CoordinateBound::UPPER_X) {
                throw std::domain_error("The x coordinate is out of bounds and the position can not be determined");
        } else if (y < CoordinateBound::LOWER_Y or y > CoordinateBound::UPPER_Y) {
                throw std::domain_error("The y coordinate is out of bounds and the position can not be determined");
        }
        this->x = x;
        this->y = y;
}

void Utils::Position::moveXPos(double distance, const Hitbox hitbox)
{
        // Set the new possible x position
        double newXPos = x + distance;

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

double Utils::Position::getX() const { return x; }

double Utils::Position::getY() const { return y; }

void Utils::Position::setPosition(Utils::Position newPos)
{
        if (newPos.x < CoordinateBound::LOWER_X or newPos.x > CoordinateBound::UPPER_X) {
                throw std::domain_error("The x coordinate is out of bounds and the position can not be determined");
        } else if (newPos.y < CoordinateBound::LOWER_Y or newPos.y > CoordinateBound::UPPER_Y) {
                throw std::domain_error("The y coordinate is out of bounds and the position can not be determined");
        }

        *this = newPos;
}