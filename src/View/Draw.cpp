/**
 * @file Draw.cpp
 * @author Basil Rommens
 * @date 12/20/19
 * @brief The cpp file of the class Draw
 */

#include "Draw.h"
#include "../Model/World.h"
#include <sstream>

// set the instance of the transformation to nullptr to be not pointing to anything
std::shared_ptr<Utils::Transformation> Utils::Transformation::instance = nullptr;

void View::Draw::onNotify(std::shared_ptr<Model::Entity> entity, Utils::Event event)
{
        switch (event) {
        case Utils::Event::UPDATE_DRAW:
                updateD(entity);
                break;
        case Utils::Event::NEW_DRAW:
                std::cout << "new" << std::endl;
                newD(entity);
                break;
        case Utils::Event::CLOSE_WINDOW:
                std::cout << "close" << std::endl;
                window->close();
                open = false;
                break;
        case Utils::Event::REMOVE:
                removeSprite(entity);
                break;
        default:
                break;
        }
}

void View::Draw::updateD(std::shared_ptr<Model::Entity> entity)
{
        std::shared_ptr<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>>> spriteToUpdate{};
        for (const auto& sprite : sprites) {
                if (sprite.first == entity) {
                        spriteToUpdate =
                            std::make_shared<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>>>(
                                sprite);
                        break;
                }
        }

        // TODO reduce code duplication with create sprite in this class
        // create an object of the transform class
        std::shared_ptr<Utils::Transformation> transform = transform->getTransformation();
        // Retrieve the sprite coordinates of the pixels
        std::pair<int, int> spriteCoordinates =
            (*transform)(entity->getPos()->getX(), entity->getPos()->getY(), window->getSize().x, window->getSize().y);

        // Place the sprite at the right position
        spriteToUpdate->second->setPosition(spriteCoordinates.first, spriteCoordinates.second);
}

void View::Draw::newD(std::shared_ptr<Model::Entity> entity)
{
        std::shared_ptr<sf::Sprite> spritePointer = std::make_shared<sf::Sprite>(createSprite(entity));
        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>> newSprite(entity, spritePointer);
        addSprite(newSprite);
}

View::Draw::Draw(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Model::World> world)
    : window(std::move(window))
{
        newD(world);
        for (std::shared_ptr<Model::Entity> entity : world->getEntities()) {
                newD(entity);
        }
}

void View::Draw::view() const
{
        window->clear();
        for (const auto& sprite : sprites) {
                window->draw(*sprite.second);
        }
        window->display();
}

void View::Draw::addSprite(std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>>& sprite)
{
        sprites.push_back(sprite);
}

void View::Draw::removeSprite(std::shared_ptr<Model::Entity> entityToRemove)
{
        for (auto sprite = sprites.begin(); sprite != sprites.end(); ++sprite) {
                if (sprite->first.get() == entityToRemove.get()) {
                        sprites.erase(sprite);
                        break;
                }
        }
}

sf::Sprite View::Draw::createSprite(std::shared_ptr<Model::Entity> entity)
{
        // TODO fix representation in texture in the model because it doesnt belong there
        // create an object of the transform class
        std::shared_ptr<Utils::Transformation> transform = transform->getTransformation();
        // Retrieve the sprite coordinates of the pixels
        std::pair<int, int> spriteCoordinates =
            (*transform)(entity->getPos()->getX(), entity->getPos()->getY(), window->getSize().x, window->getSize().y);

        std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>(sf::Texture());
        if (not textures[entity->getImage()]) {
                texture->loadFromFile(entity->getImage());
                textures[entity->getImage()] = texture;
        }

        // create the sprite and apply the next 3 actions on it
        sf::Sprite sprite;
        // 1. Decide the texture of the sprite
        sprite.setTexture(*textures[entity->getImage()]);

        // 2. Place the sprite at the right position
        sprite.setPosition(spriteCoordinates.first, spriteCoordinates.second);

        // 3. Set the scale of the sprite according to the window size
        // TODO add the default window size in utils namespace
        sprite.scale(sf::Vector2f(window->getSize().x / 800.f, window->getSize().y / 600.f));
        return sprite;
}

std::string View::Draw::getType() const { return "draw"; }

bool View::Draw::isOpen() const { return open; }

View::Draw::~Draw()
{
        sprites.clear();
        textures.clear();
        window.reset();
}
