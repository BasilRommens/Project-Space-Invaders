/**
 * @file 
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_POSITION_H
#define PROJECT_SPACE_INVADERS_POSITION_H

namespace Utils {

    class Position {
        double xPos{};
        double yPos{};
    public:
        Position(double x_pos, double y_pos);
    };

}

#endif //PROJECT_SPACE_INVADERS_POSITION_H
