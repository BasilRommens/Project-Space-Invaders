/**
 * @file Hitbox.h
 * @author Basil Rommens
 * @date 12/28/19
 * @brief The header file of the class Hitbox
 */

#ifndef PROJECT_SPACE_INVADERS_HITBOX_H
#define PROJECT_SPACE_INVADERS_HITBOX_H

class Hitbox {
private:
    double width{};
    double height{};
public:
    Hitbox(double width, double height);
};

#endif //PROJECT_SPACE_INVADERS_HITBOX_H
