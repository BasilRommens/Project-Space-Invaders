/**
 * @file Draw.h
 * @author Basil Rommens
 * @date 12/20/19
 * @brief The header file of the class Draw
 */

#ifndef PROJECT_SPACE_INVADERS_DRAW_H
#define PROJECT_SPACE_INVADERS_DRAW_H

#include <SFML/Graphics.hpp>

#include "ObserverPattern/Observer.h"
#include "utils/Transformation.h"
#include "Entity/Entity.h"
#include "Entity/EnemyShip.h"
#include "Entity/Bullet.h"
#include "Entity/BGTile.h"
#include "Entity/PlayerShip.h"

namespace EntityNS {

    class World;

}

class Draw : public Observer {
private:
    std::vector<sf::Texture> textures;

    std::shared_ptr<sf::RenderWindow> window;

    std::vector<std::pair<std::shared_ptr<EntityNS::Entity>, std::shared_ptr<sf::Sprite>>> sprites;

    sf::Sprite createSprite(std::shared_ptr<EntityNS::Entity> entity);

public:
    Draw(const std::shared_ptr<sf::RenderWindow>& window, const EntityNS::World& world);

    void onNotify(std::shared_ptr<EntityNS::Entity> entity, Utils::Event event) override;

    void updateD(std::shared_ptr<EntityNS::Entity> entity);

    void newD(std::shared_ptr<EntityNS::Entity> entity);

    void view() const;

    void addSprite(std::pair<std::shared_ptr<EntityNS::Entity>, std::shared_ptr<sf::Sprite>>& sprite);

    void removeSprite(std::pair<std::shared_ptr<EntityNS::Entity>, std::shared_ptr<sf::Sprite>>& sprite);

    std::string getType() override;
};

#endif //PROJECT_SPACE_INVADERS_DRAW_H
