/**
 * @file Draw.cpp
 * @author Basil Rommens
 * @date 12/20/19
 * @brief The cpp file of the class Draw
 */

#include "Draw.h"

void Draw::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    switch (event) {
    case Utils::Event::UPDATE_DRAW:
        updateD(entity);
        break;
    case Utils::Event::NEW_DRAW:
        newD(entity);
        break;
    default:
        break;
    }
}

void Draw::updateD(std::shared_ptr<Entity> entity)
{

}

void Draw::newD(std::shared_ptr<Entity> entity)
{
    std::pair<std::shared_ptr<Entity>, sf::Sprite> t(entity,);
}

Draw::Draw(const std::shared_ptr<sf::RenderWindow>& window, const World& world)
        :window(window) {
    // TODO add all the world elements to the draw
}

void Draw::view() const
{
    window->clear();
    for (const auto& sprite: sprites) {
        window->draw(sprite.second);
    }
    window->display();
}

void Draw::addSprite(std::pair<std::shared_ptr<Entity>, sf::Sprite>& sprite)
{
    sprites.push_back(sprite);
}

void Draw::removeSprite(std::pair<std::shared_ptr<Entity>, sf::Sprite>& sprite)
{
    sprites.erase(std::find(sprites.begin(), sprites.end(), sprite));
}

sf::Sprite Draw::createSprite(std::shared_ptr<Entity> entity)
{
    // TODO scale sprites
    std::shared_ptr<Utils::Transformation> transform = transform->getTransformation();
    std::pair<unsigned int, unsigned int> spriteCoordinates = (*transform)(entity->getPos().getXPos(),
            entity->getPos().getYPos(), window->getSize().x);

    sf::Texture texture;
    texture.loadFromFile(entity->getImage());

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sprite.setOrigin(spriteCoordinates.first, spriteCoordinates.second);

    return sprite;
}
