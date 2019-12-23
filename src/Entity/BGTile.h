/**
 * @file 
 * @author Basil Rommens
 * @date 22/11/2019
 * @brief ...
 */

#ifndef PROJECT_SPACE_INVADERS_BGTILE_H
#define PROJECT_SPACE_INVADERS_BGTILE_H

#include "Entity.h"

namespace EntityNS {

    class BGTile : public Entity {
    public:
        std::string getType() const override;

    };

}

#endif //PROJECT_SPACE_INVADERS_BGTILE_H
