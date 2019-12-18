/**
 * @file Position.h
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The header file of the position class
 */

#ifndef PROJECT_SPACE_INVADERS_POSITION_H
#define PROJECT_SPACE_INVADERS_POSITION_H

#include "Transformation.h"

namespace Utils {

    enum Direction {
        UP,
        DOWN
    };

    class Position {
    private:
        double xPos{};
        double yPos{};
    public:
        Position(double x_pos, double y_pos);

        void moveXPos(double distance);

        void moveYPos(double distance);
    };

}

#endif //PROJECT_SPACE_INVADERS_POSITION_H
