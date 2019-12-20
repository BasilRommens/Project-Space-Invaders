/**
 * @file Event.h
 * @author Basil Rommens
 * @date 12/17/19
 * @brief The file that contains the enum type of all the possible events
 */

namespace Utils {

    enum Event {
        UPDATE_DRAW,
        MOVE_RIGHT,
        MOVE_LEFT,
        FIRE_BULLET,
        CLOSE_WINDOW,
        NEW_DRAW
    };

}