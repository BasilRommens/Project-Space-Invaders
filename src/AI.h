/**
 * @file AI.h
 * @author Basil Rommens
 * @date 12/22/19
 * @brief The header file of the class AI
 */

#ifndef PROJECT_SPACE_INVADERS_AI_H
#define PROJECT_SPACE_INVADERS_AI_H

#include "Subject.h"

class AI : public Subject, public Observer {
private:

public:
    AI();

    void onNotify(std::shared_ptr<EntityNS::Entity> entity, Utils::Event event) override { }
};

#endif //PROJECT_SPACE_INVADERS_AI_H
