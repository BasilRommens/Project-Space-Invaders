/**
 * @file Draw.h
 * @author Basil Rommens
 * @date 12/20/19
 * @brief The header file of the class Draw
 */

#ifndef PROJECT_SPACE_INVADERS_DRAW_H
#define PROJECT_SPACE_INVADERS_DRAW_H

#include <SFML/Graphics.hpp>

#include "Utils/ObserverPattern/Observer.h"
#include "../utils/Transformation.h"
#include "../Entity/Entity.h"
#include "../Entity/EnemyShip.h"
#include "../Entity/Bullet.h"
#include "../Entity/BGTile.h"
#include "../Entity/PlayerShip.h"

namespace Model {

    class World;

}

namespace View {

    class Draw : public ObserverPattern::Observer {
    private:
        bool open{true}; ///< is a variable to check if the window still is open

        std::vector<sf::Texture> textures;

        std::shared_ptr<sf::RenderWindow> window;

        std::vector<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>>> sprites;

        sf::Sprite createSprite(std::shared_ptr<Model::Entity> entity);

    public:
        Draw(const std::shared_ptr<sf::RenderWindow>& window, const Model::World& world);

        void onNotify(std::shared_ptr<Model::Entity> entity, Utils::Event event) final;

        void updateD(std::shared_ptr<Model::Entity> entity);

        void newD(std::shared_ptr<Model::Entity> entity);

        void view() const;

        void addSprite(std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>>& sprite);

        void removeSprite(std::shared_ptr<Model::Entity> entityToRemove);

        std::string getType() final;

        bool isOpen() const;
    };

}

#endif //PROJECT_SPACE_INVADERS_DRAW_H
