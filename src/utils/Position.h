/**
 * @file Position.h
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The header file of the position class
 */

#ifndef PROJECT_SPACE_INVADERS_POSITION_H
#define PROJECT_SPACE_INVADERS_POSITION_H

#include <stdexcept>

#include "Hitbox.h"
#include "Transformation.h"

/**
 * @addtogroup Utils
 * @{
 */
namespace Utils {

/**
 * @enum Direction: The direction in which an object moves
 */
enum Direction
{
        UP,
        DOWN,
        LEFT,
        RIGHT
};

/**
 * @brief The class that keeps a 2 dimensional position of the world
 * @details It needs to stay inside the bounds that are defined in the Transformation.h file
 * @see Transformation.h
 */
class Position
{
private:
        double x; ///< The x position in the coordinate system bounded by the transformation file @see Transformation.h
        double y; ///< The x position in the coordinate system decided by the transformation file @see Transformation.h
public:
        /**
         * @brief The constructor of the Position class with both the x and y value to be set
         * @param x: The x value to be set as the x position (default 0)
         * @param y: The y value to be set as the y position (default 0)
         * @throws std::domain_error If the x coordinate is lower or higher than the world bounds
         * @throws std::domain_error If the y coordinate is lower or higher than the world bounds
         */
        explicit Position(double x = 0.f, double y = 0.f);

        /**
         * @brief moves the x value over a certain distance while keeping it in the bounds declared in the
         * transformation file @see Transformation.h
         * @param distance: The distance over which we need to move the x value
         * @param hitbox: The hitbox of the object to be moved
         * @throws std::out_of_range If we hit one of the width bounds with the hitbox
         */
        void moveXPos(double distance, Hitbox hitbox);

        /**
         * @brief moves the y value over a certain distance while keeping it in the bounds declared in the
         * transformation file @see Transformation.h
         * @param distance: The distance over which we need to move the y value
         * @brief hitbox: The hitbox of the object to be moved
         * @throws std::out_of_range If we hit one of the height bounds with the hitbox
         */
        void moveYPos(double distance, Hitbox hitbox);

        /**
         * @return The x value of the position
         */
        double getX() const;

        /**
         * @return The y value of the position
         */
        double getY() const;

        /**
         * @brief sets the position by the new position passed through via a parameter
         * @param newPosition: The new position to be set as the current position
         * @throws std::domain_error If the x coordinate of the newPosition is out of bounds
         * @throws std::domain_error If the y coordinate of the newPosition is out of bounds
         */
        void setPosition(Utils::Position newPosition);
};

} // namespace Utils

/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_POSITION_H
