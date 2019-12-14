/**
 * @file Transformation.h
 * @author Basil Rommens
 * @date 12/11/19
 * @brief The header file of the Transformation class
 * @source https://www.tutorialspoint.com/Explain-Cplusplus-Singleton-design-pattern
 */

#ifndef PROJECT_SPACE_INVADERS_TRANSFORMATION_H
#define PROJECT_SPACE_INVADERS_TRANSFORMATION_H

class Transformation {
private:
    static Transformation* instance; /** @var instance: The sole instance of the Transformation class */

    /**
     * @brief The default constructor of Transformation
     */
    Transformation();

public:
    /**
     *
     * @return The sole instance of an object of this class
     */
    static Transformation* getTransformation();
};

#endif //PROJECT_SPACE_INVADERS_TRANSFORMATION_H
