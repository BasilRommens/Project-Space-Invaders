/**
 * @file Font.h
 * @author Basil Rommens
 * @date 1/19/20
 * @brief The global variables of the project
 */
#ifndef PROJECT_SPACE_INVADERS_GLOBAL_H
#define PROJECT_SPACE_INVADERS_GLOBAL_H

#include <string>

/**
 * @addtogroup Utils
 * @{
 */
namespace Utils {
const std::string font = "input/Roboto/Roboto-Black.ttf"; ///< The default font to use
const double count = 1000000.f;   ///< The value to multiply with when we want to get the count in seconds
const float windowHeight = 600.f; ///< The default window height
const float windowWidth = 800.f;  ///< The default window width
} // namespace Utils
/**
 * @}
 */

#endif // PROJECT_SPACE_INVADERS_GLOBAL_H
