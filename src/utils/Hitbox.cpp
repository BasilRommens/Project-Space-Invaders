/**
 * @file Hitbox.cpp
 * @author Basil Rommens
 * @date 12/28/19
 * @brief The cpp file of the class Hitbox
 */

#include "Hitbox.h"

Utils::Hitbox::Hitbox(double width, double height) {
    if (width <= 0 or height <= 0) {
        throw std::domain_error("Hitbox::Hitbox(double width, double height) : The width or height is too small to be a hitbox");
    }
    this->width = width;
    this->height = height;
}

double Utils::Hitbox::getWidth() const { return width; }

double Utils::Hitbox::getHeight() const { return height; }