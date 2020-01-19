/**
 * @file Draw.cpp
 * @author Basil Rommens
 * @date 12/20/19
 * @brief The cpp file of the class Draw
 */

#include "Draw.h"
#include "../Model/World.h"
#include "../utils/Global.h"
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
                newD(entity);
                break;
        case Utils::Event::CLOSE_WINDOW:
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
        if (not entity) {
                throw std::invalid_argument("View::Draw::updateD(std::shared_ptr<Model::Entity>) : There is no entity "
                                            "which we can update the sprite from");
        }
        std::shared_ptr<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>>> spriteToUpdate{};
        for (const auto& sprite : sprites) {
                if (sprite.first == entity) {
                        spriteToUpdate =
                            std::make_shared<std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>>>(
                                sprite);
                        break;
                }
        }

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
        if (not entity) {
                throw std::invalid_argument("View::Draw::newD(std::shared_ptr<Model::Entity>) : There is no entity "
                                            "from which we can draw the sprite");
        }
        std::shared_ptr<sf::Sprite> spritePointer = std::make_shared<sf::Sprite>(createSprite(entity));
        std::pair<std::shared_ptr<Model::Entity>, std::shared_ptr<sf::Sprite>> newSprite(entity, spritePointer);
        addSprite(newSprite);
}

View::Draw::Draw(std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<Model::World> world)
{
        if (not window) {
                throw std::invalid_argument("View::Draw::Draw(...) : There is no window to be found");
        } else if (not world) {
                throw std::invalid_argument("View::Draw::Draw(...) : There is no world to be found");
        }
        this->window = std::move(window);
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
        // create an object of the transform class
        std::shared_ptr<Utils::Transformation> transform = transform->getTransformation();
        // Retrieve the sprite coordinates of the pixels
        std::pair<int, int> spriteCoordinates; // sprite coordinates on the view
        // If the entity is a world then set the coordinates of the sprite to the top left of the screen
        if (entity->getType() == "world") {
                spriteCoordinates = std::make_pair<int, int>(0, 0);
        } // Otherwise change the coordinates of the sprite according to the current entity position
        else {
                spriteCoordinates = (*transform)(entity->getPos()->getX(), entity->getPos()->getY(),
                                                 window->getSize().x, window->getSize().y);
        }

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
        // If it is of the type world then we need to fit the image over the whole screen
        if (entity->getType() == "world") {
                sprite.scale(Utils::windowWidth / sprite.getGlobalBounds().width,
                             Utils::windowHeight / sprite.getGlobalBounds().height);
        } // Otherwise we mustn't and we scale according to the standard screen size
        else {
                sprite.scale(
                    sf::Vector2f(window->getSize().x / Utils::windowWidth, window->getSize().y / Utils::windowHeight));
        }
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
