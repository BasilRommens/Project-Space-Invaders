/**
 * @file Hitbox.h
 * @author Basil Rommens
 * @date 12/28/19
 * @brief The header file of the class Hitbox
 */

#ifndef PROJECT_SPACE_INVADERS_HITBOX_H
#define PROJECT_SPACE_INVADERS_HITBOX_H

/**
 * @addtogroup Utils
 * @{
 */
namespace Utils {

    /**
     * @brief The class that is used to describe the hitbox of the entity that uses it
     * @details it can be measured from the top right corner
     */
    class Hitbox {
    private:
        double width{}; ///< The width of the Hitbox
        double height{}; ///< The height of the Hitbox
    public:
        /**
         * @brief The constructor of the hitbox class
         * TODO ensure that the width and height isnt negative else throw an error
         */
        Hitbox(double width = 0.f, double height = 0.f);

        /**
         * @return The width of the hitbox
         */
        double getWidth() const;

        /**
         * @return The height of the hitbox
         */
        double getHeight() const;
    };

}
/**
 * @}
 */

#endif //PROJECT_SPACE_INVADERS_HITBOX_H
