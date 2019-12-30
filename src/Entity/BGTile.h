/**
 * @file BGTile.h
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief The header file of the class BGTile
 */

#ifndef PROJECT_SPACE_INVADERS_BGTILE_H
#define PROJECT_SPACE_INVADERS_BGTILE_H

#include "Entity.h"

/**
 * @addtogroup EntityNS
 * @{
 */
namespace EntityNS {

    class BGTile : public Entity {
    public:
        /**
         * @brief The destructor of the BGTile class
         */
        virtual ~BGTile();

        /**
         * @return The type ("BGTile") of the class
         */
        std::string getType() const final;
    };

}
/**
 * @}
 */

#endif //PROJECT_SPACE_INVADERS_BGTILE_H
