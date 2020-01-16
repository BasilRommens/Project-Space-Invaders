/**
 * @file Position.h
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The header file of the position class
 */

#ifndef PROJECT_SPACE_INVADERS_POSITION_H
#define PROJECT_SPACE_INVADERS_POSITION_H

#include "Transformation.h"
#include "Hitbox.h"

/**
 * @addtogroup Utils
 * @{
 */
namespace Utils {

    /**
     * @enum Direction: The direction in which an object moves
     */
    enum Direction {
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
    class Position {
    private:
        double x{}; ///< The x position in the coordinate system bounded by the transformation file @see Transformation.h
        double y{}; ///< The x position in the coordinate system decided by the transformation file @see Transformation.h
    public:
        /**
         * @brief The default constructor of the Position class
         */
        Position();

        /**
         * @brief The constructor of the Position class with both the x and y value to be set
         * @param x: The x value to be set as the x position
         * @param y: The y value to be set as the y position
         */
        // TODO add a check if within bounds
        Position(double x, double y);

        /**
         * @brief moves the x value over a certain distance while keeping it in the bounds declared in the transformation file @see Transformation.h
         * @param distance: The distance over which we need to move the x value
         * @param hitbox:
         */
        void moveXPos(double distance, Hitbox hitbox);

        /**
         * @brief moves the y value over a certain distance while keeping it in the bounds declared in the transformation file @see Transformation.h
         * @param distance: The distance over which we need to move the y value
         * @brief hitbox:
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
         */
        // TODO add check if the coordinates are within bounds
        void setPosition(Utils::Position newPosition);
    };

}

/**
 * @}
 */

#endif //PROJECT_SPACE_INVADERS_POSITION_H
