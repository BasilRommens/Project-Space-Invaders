/**
 * @file Hitbox.cpp
 * @author Basil Rommens
 * @date 12/28/19
 * @brief The cpp file of the class Hitbox
 */

#include "Hitbox.h"

Utils::Hitbox::Hitbox(double width, double height) : width(width), height(height) {}

double Utils::Hitbox::getWidth() const { return width; }

double Utils::Hitbox::getHeight() const { return height; }