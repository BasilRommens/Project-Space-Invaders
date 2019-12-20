/**
 * @file Draw.h
 * @author Basil Rommens
 * @date 12/20/19
 * @brief The header file of the class Draw
 */

#ifndef PROJECT_SPACE_INVADERS_DRAW_H
#define PROJECT_SPACE_INVADERS_DRAW_H

#include <SFML/Graphics.hpp>

#include "Observer.h"
#include "utils/Transformation.h"
#include "Entity/Entity.h"
#include "Entity/EnemyShip.h"
#include "Entity/Bullet.h"
#include "Entity/BGTile.h"
#include "Entity/PlayerShip.h"
#include "Entity/World.h"

std::shared_ptr<Utils::Transformation> Utils::Transformation::instance = nullptr;

class Draw : public Observer {
private:
    std::shared_ptr<sf::RenderWindow> window;

    std::vector<std::pair<std::shared_ptr<Entity>, sf::Sprite>> sprites;

    sf::Sprite createSprite(std::shared_ptr<Entity> entity);

public:
    Draw(const std::shared_ptr<sf::RenderWindow>& window, const World& world);

    void onNotify(std::shared_ptr<Entity> entity, Utils::Event event) override;

    void updateD(std::shared_ptr<Entity> entity);

    void newD(std::shared_ptr<Entity> entity);

    void view() const;

    void addSprite(std::pair<std::shared_ptr<Entity>, sf::Sprite>& sprite);

    void removeSprite(std::pair<std::shared_ptr<Entity>, sf::Sprite>& sprite);
};

#endif //PROJECT_SPACE_INVADERS_DRAW_H
