/**
 * @file Transformation.cpp
 * @author Basil Rommens
 * @date 12/11/19
 * @brief The cpp file of the transformation class
 */

#include "Transformation.h"

Utils::Transformation::Transformation() { }

std::shared_ptr<Utils::Transformation>& Utils::Transformation::getTransformation()
{
    // If the Transformation object has not yet been constructed
    if (!instance) {
        instance = std::shared_ptr<Transformation>(new Transformation());
    }
    return instance;
}

std::pair<unsigned int, unsigned int> Utils::Transformation::operator()(double x, double y, unsigned int width)
{
    double scaleWidth = width/(-CoordinateBound::LOWER_X+CoordinateBound::UPPER_X);
    double height = width*(-CoordinateBound::LOWER_Y*CoordinateBound::UPPER_Y)
            /(-CoordinateBound::LOWER_X*CoordinateBound::UPPER_Y);
    double scaleHeight = height/(-CoordinateBound::LOWER_Y+CoordinateBound::UPPER_Y);

    try {
        // change the coordinates in the [-4,4] x [-3,3] system to the screen pixels
        double retX = (x-CoordinateBound::LOWER_X)*scaleWidth;
        double retY = (y-CoordinateBound::LOWER_Y)*scaleHeight;

        // exception handling
        std::string e; // Initializing the out of range exception with nothing
        bool throwIt = false;
        if (retX<0) {
            e = "retX is too small to be on screen\n";
            throwIt = true;
        }
        else if (retX>width) {
            e = "retX is too big to be on screen\n";
            throwIt = true;
        }

        if (retY<0) {
            throw std::out_of_range(e+"retY is too small to be on screen");
        }
        else if (retY>height) {
            throw std::out_of_range(e+"retY is too big to be on screen");
        }
        else if (throwIt) {
            throw std::out_of_range(e);
        }

        return std::make_pair(std::round(retX), std::round(retY));
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return std::make_pair(0, 0);
    }
}
