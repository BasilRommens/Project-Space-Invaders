/**
 * @file Transformation.cpp
 * @author Basil Rommens
 * @date 12/11/19
 * @brief The cpp file of the transformation class
 */

#include "Transformation.h"

Utils::Transformation::Transformation()
{

}

Utils::Transformation Utils::Transformation::getTransformation()
{
    static Transformation instance = Transformation();
    return instance;
}

std::pair<unsigned int, unsigned int> Utils::Transformation::operator()(double x, double y, unsigned int width)
{
    double scaleWidth = width/(-CoordinateBound::LOWER_X+CoordinateBound::UPPER_X);
    double height = width*(-CoordinateBound::LOWER_Y*CoordinateBound::UPPER_Y)
            /(-CoordinateBound::LOWER_X*CoordinateBound::UPPER_Y);
    double scaleHeight = height/(-CoordinateBound::LOWER_Y+CoordinateBound::UPPER_Y);

    // change the coordinates in the [-4,4] x [-3,3] system to the screen pixels
    double retX = (x-CoordinateBound::LOWER_X)*scaleWidth;
    double retY = (y-CoordinateBound::LOWER_Y)*scaleHeight;

    return std::make_pair(std::round(retX), std::round(retY));

}
