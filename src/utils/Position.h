/**
 * @file Position.h
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The header file of the position class
 */

#ifndef PROJECT_SPACE_INVADERS_POSITION_H
#define PROJECT_SPACE_INVADERS_POSITION_H

namespace Utils {

    enum Direction {
        UP,
        DOWN
    };

    class Position {
        double xPos{};
        double yPos{};
    public:
        Position(double x_pos, double y_pos);
    };

}

#endif //PROJECT_SPACE_INVADERS_POSITION_H
