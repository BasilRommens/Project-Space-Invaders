/**
 * @file Draw.cpp
 * @author Basil Rommens
 * @date 12/20/19
 * @brief The cpp file of the class Draw
 */

#include "Draw.h"

// set the instance of the transformation to nullptr to be not pointing to anything
std::shared_ptr<Utils::Transformation> Utils::Transformation::instance = nullptr;

void Draw::onNotify(std::shared_ptr<Entity> entity, Utils::Event event)
{
    switch (event) {
    case Utils::Event::UPDATE_DRAW:
        std::cout << "update" << std::endl;
        updateD(entity);
        break;
    case Utils::Event::NEW_DRAW:
        std::cout << "new" << std::endl;
        newD(entity);
        break;
    case Utils::Event::CLOSE_WINDOW:
        std::cout << "close" << std::endl;
        window->close();
        break;
    default:
        break;
    }
}

void Draw::updateD(std::shared_ptr<Entity> entity)
{
    std::shared_ptr<std::pair<std::shared_ptr<Entity>, sf::Sprite>> spriteToUpdate;
    for (auto sprite: sprites) {
        if (sprite.first.get()==entity.get()) {
            spriteToUpdate = std::make_shared<std::pair<std::shared_ptr<Entity>, sf::Sprite>>(sprite);
            break;
        }
    }
    // TODO recalculate the place of the spriteToUpdate
}

void Draw::newD(std::shared_ptr<Entity> entity)
{
    std::pair<std::shared_ptr<Entity>, sf::Sprite> newSprite(entity, createSprite(entity));
    this->sprites.push_back(newSprite);
}

Draw::Draw(const std::shared_ptr<sf::RenderWindow>& window, const World& world)
        :window(window)
{
    for (auto entity: world.getEntities()) {
        newD(entity);

    }
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
    // TODO fix the sprite datastructure because the sprites seem to be stored by value and not by memory location
    for (auto _sprite = sprites.begin(); _sprite!=sprites.end(); ++_sprite) {
        if (_sprite->first.get()==sprite.first.get() and &_sprite->second==&sprite.second) {
            sprites.erase(_sprite);
            break;
        }
    }
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
