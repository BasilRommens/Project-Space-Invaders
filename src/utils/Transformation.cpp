/**
 * @file Transformation.cpp
 * @author Basil Rommens
 * @date 12/11/19
 * @brief The cpp file of the transformation class
 */

#include "Transformation.h"

Transformation::Transformation()
{

}

Transformation Transformation::getTransformation()
{
    static Transformation instance = Transformation();
    return instance;
}

std::pair<unsigned int, unsigned int> Transformation::operator()(double x, double y, unsigned int width)
{
    double scaleWidth = width/(-lowerX+upperX);
    double height = width*(-lowerY*upperY)/(-lowerX*upperX);
    double scaleHeight = height/(-lowerY+upperY);

    // change the coordinates in the [-4,4] x [-3,3] system to the screen pixels
    double retX = (x-lowerX)*scaleWidth;
    double retY = (y-lowerY)*scaleHeight;

    return std::make_pair(std::round(retX), std::round(retY));

}
