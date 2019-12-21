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
    std::cout << "update" << std::endl;
    // TODO recalculate the place of the spriteToUpdate
}

void Draw::newD(std::shared_ptr<Entity> entity)
{
    std::pair<std::shared_ptr<Entity>, sf::Sprite> newSprite(entity, createSprite(entity));
    addSprite(newSprite);
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
    // TODO fix representation in texture in the model because it doesnt belong there
    // create an object of the transform class
    std::shared_ptr<Utils::Transformation> transform = transform->getTransformation();
    // Retrieve the sprite coordinates of the pixels
    std::pair<int, int> spriteCoordinates = (*transform)(entity->getPos().getXPos(),
            entity->getPos().getYPos(), window->getSize().x, window->getSize().y);

    sf::Texture texture;
    texture.loadFromFile(entity->getImage());
    textures.push_back(texture);

    // create the sprite and apply the next 3 actions on it
    sf::Sprite sprite;
    // Decide the texture of the sprite
    sprite.setTexture(entity->getTexture());

    // Place the sprites at the right position
    sprite.setPosition(spriteCoordinates.first, spriteCoordinates.second);

    // TODO fix scaling of sprites
    // Set the scale of the sprite according to the window size
    sprite.scale(sf::Vector2f(window->getSize().x/800.f, window->getSize().y/600.f));
    return sprite;
}
