/**
 * @file Transformation.h
 * @author Basil Rommens
 * @date 12/11/19
 * @brief The header file of the Transformation class
 * @source https://www.tutorialspoint.com/Explain-Cplusplus-Singleton-design-pattern
 */

#ifndef PROJECT_SPACE_INVADERS_TRANSFORMATION_H
#define PROJECT_SPACE_INVADERS_TRANSFORMATION_H

#include <tuple>
#include <cmath>
#include <exception>
#include <memory>

const double upperX = 4;
const double lowerX = -4;
const double upperY = 3;
const double lowerY = -3;

class Transformation {
private:
    static Transformation instance; /** @var instance: The sole instance of the Transformation class */

    /**
     * @brief The default constructor of Transformation
     */
    Transformation();

public:
    /**
     *
     * @return The sole instance of an object of this class
     */
    static Transformation getTransformation();

    std::pair<unsigned int, unsigned int> operator()(double x, double y, unsigned int width);
};

#endif //PROJECT_SPACE_INVADERS_TRANSFORMATION_H
