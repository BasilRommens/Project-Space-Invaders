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

namespace Utils {

    namespace CoordinateBound {
        const double UPPER_X = 4;
        const double LOWER_X = -4;
        const double UPPER_Y = 3;
        const double LOWER_Y = -3;
    }

    class Transformation {
    private:
        static Transformation instance; /** @var instance: The sole instance of the Transformation class */

        /**
         * @brief The default constructor of Transformation
         */
        Transformation();

    public:
        /**
         * @return The sole instance of an object of this class
         */
        static Transformation getTransformation();

        /**
         * @param x: The x position in the [-4,4] x [-3, 3] coordinate system
         * @param y: The y position in the [-4,4] x [-3, 3] coordinate system
         * @param width: The width of the screen
         * @return The coordinates in pixels of the coordinates in the [-4,4] x [-3, 3] coordinate system
         */
        std::pair<unsigned int, unsigned int> operator()(double x, double y, unsigned int width);
    };

}

#endif //PROJECT_SPACE_INVADERS_TRANSFORMATION_H
