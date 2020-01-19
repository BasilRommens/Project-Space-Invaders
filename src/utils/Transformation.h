/**
 * @file Transformation.h
 * @author Basil Rommens
 * @date 12/11/19
 * @brief The header file of the Transformation class
 * @see https://stackoverflow.com/questions/47558290/singleton-class-with-smart-pointers-and-destructor-being-called
 */

#ifndef PROJECT_SPACE_INVADERS_TRANSFORMATION_H
#define PROJECT_SPACE_INVADERS_TRANSFORMATION_H

#include <cmath>
#include <exception>
#include <iostream>
#include <memory>
#include <tuple>

/**
 * @addtogroup Utils
 * @{
 */
namespace Utils {

/**
 * @addtogroup CoordinateBound
 * @{
 */
namespace CoordinateBound {
const double UPPER_X = 4;  ///< The upper coordinate on the x-axis
const double LOWER_X = -4; ///< The lower coordinate on the x-axis
const double UPPER_Y = 3;  ///< The upper coordinate on the y-axis
const double LOWER_Y = -3; ///< The lower coordinate on the y-axis
} // namespace CoordinateBound
/**
 * @}
 */

/**
 * @brief This class returns the values from the given coordinate system to the display in pixels
 * @details This class has just the call operator implemented (forget the constructor for a little while) in order to
 * simplify the use of transformations in the game
 */
class Transformation
{
private:
        static std::shared_ptr<Transformation> instance; ///< The sole instance of the Transformation class

        /**
         * @brief The default constructor of Transformation
         */
        Transformation() = default;

public:
        /**
         * @return The sole instance of an object of this class
         */
        static std::shared_ptr<Transformation>& getTransformation();

        /**
         * @param x: The x position in the [-4,4] x [-3, 3] coordinate system
         * @param y: The y position in the [-4,4] x [-3, 3] coordinate system
         * @param width: The width of the window
         * @return The coordinates in pixels of the coordinates in the [-4,4] x [-3, 3] coordinate system
         * @throws std::out_of_range when the x coordinate is too big to be on the screen width
         * @throws std::out_of_range when the y coordinate is too big to be on the screen height
         */
        std::pair<int, int> operator()(double x, double y, unsigned int width, unsigned int height);
};

} // namespace Utils
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_TRANSFORMATION_H
