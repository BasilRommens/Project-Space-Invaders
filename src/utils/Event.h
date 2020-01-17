/**
 * @file Event.h
 * @author Basil Rommens
 * @date 12/17/19
 * @brief The file that contains the enum type of all the possible events
 */

/**
 * @namespace Utils We can use this namespace in order to indicate the files that are useful for the creation of the project
 */

/**
 * @addtogroup Utils
 * @{
 */
namespace Utils {

    /**
     * @enum Event: All the events possible in the game
     */
    enum Event {
        MOVED_DOWN,
        UPDATE_DRAW,
        MOVE_RIGHT,
        MOVE_LEFT,
        MOVE,
        FIRE_BULLET,
        CLOSE_WINDOW,
        NEW_DRAW,
        UNMOVE,
        DECREASE_DELAY,
        CHECK_COLLISIONS,
        REMOVE
    };

}

/**
 * @}
 */