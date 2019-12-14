/**
 * @file Transformation.cpp
 * @author Basil Rommens
 * @date 12/11/19
 * @brief The cpp file of the transformation class
 */

#include "Transformation.h"

Transformation::Transformation()
{

}

Transformation* Transformation::getTransformation()
{
    if (!instance)
        instance = new Transformation();
    return instance;
}
