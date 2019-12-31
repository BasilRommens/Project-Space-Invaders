/**
 * @file Event.h
 * @author Basil Rommens
 * @date 12/17/19
 */

/**
 * @addtogroup Utils
 * @{
 */

/**
 * @brief The file that contains the enum type of all the possible events
 */
namespace Utils {

    /**
     * @enum Event: All the events possible in the game
     */
    enum Event {
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