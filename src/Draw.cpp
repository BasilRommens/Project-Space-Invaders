/**
 * @file Draw.cpp
 * @author Basil Rommens
 * @date 12/20/19
 * @brief The cpp file of the class Draw
 */

#include "Draw.h"
#include "Entity/World.h"

// set the instance of the transformation to nullptr to be not pointing to anything
std::shared_ptr<Utils::Transformation> Utils::Transformation::instance = nullptr;

void Draw::onNotify(std::shared_ptr<EntityNS::Entity> entity, Utils::Event event)
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
        open = false;
        break;
    default:
        break;
    }
}

void Draw::updateD(std::shared_ptr<EntityNS::Entity> entity)
{
    std::shared_ptr<std::pair<std::shared_ptr<EntityNS::Entity>, std::shared_ptr<sf::Sprite>>> spriteToUpdate;
    for (auto sprite: sprites) {
        if (sprite.first.get()==entity.get()) {
            spriteToUpdate = std::make_shared<std::pair<std::shared_ptr<EntityNS::Entity>, std::shared_ptr<sf::Sprite>>>(
                    sprite);
            break;
        }
    }

    // TODO reduce code duplication with create sprite in this class
    // create an object of the transform class
    std::shared_ptr<Utils::Transformation> transform = transform->getTransformation();
    // Retrieve the sprite coordinates of the pixels
    std::pair<int, int> spriteCoordinates = (*transform)(entity->getPos()->getX(),
            entity->getPos()->getY(), window->getSize().x, window->getSize().y);

    // Place the sprite at the right position
    spriteToUpdate->second->setPosition(spriteCoordinates.first, spriteCoordinates.second);
}

void Draw::newD(std::shared_ptr<EntityNS::Entity> entity)
{
    std::shared_ptr<sf::Sprite> spritePointer = std::make_shared<sf::Sprite>(createSprite(entity));
    std::pair<std::shared_ptr<EntityNS::Entity>, std::shared_ptr<sf::Sprite>> newSprite(entity, spritePointer);
    addSprite(newSprite);
}

Draw::Draw(const std::shared_ptr<sf::RenderWindow>& window, const EntityNS::World& world)
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
        window->draw(*sprite.second);
    }
    window->display();
}

void Draw::addSprite(std::pair<std::shared_ptr<EntityNS::Entity>, std::shared_ptr<sf::Sprite>>& sprite)
{
    sprites.push_back(sprite);
}

void Draw::removeSprite(std::pair<std::shared_ptr<EntityNS::Entity>, std::shared_ptr<sf::Sprite>>& sprite)
{
    for (auto _sprite = sprites.begin(); _sprite!=sprites.end(); ++_sprite) {
        if (_sprite->first.get()==sprite.first.get() and _sprite->second.get()==sprite.second.get()) {
            sprites.erase(_sprite);
            break;
        }
    }
}

sf::Sprite Draw::createSprite(std::shared_ptr<EntityNS::Entity> entity)
{
    // TODO fix representation in texture in the model because it doesnt belong there
    // create an object of the transform class
    std::shared_ptr<Utils::Transformation> transform = transform->getTransformation();
    // Retrieve the sprite coordinates of the pixels
    std::pair<int, int> spriteCoordinates = (*transform)(entity->getPos()->getX(),
            entity->getPos()->getY(), window->getSize().x, window->getSize().y);

    sf::Texture texture;
    texture.loadFromFile(entity->getImage());
    textures.push_back(texture);

    // create the sprite and apply the next 3 actions on it
    sf::Sprite sprite;
    // 1. Decide the texture of the sprite
    sprite.setTexture(entity->getTexture());

    // 2. Place the sprite at the right position
    sprite.setPosition(spriteCoordinates.first, spriteCoordinates.second);

    // 3. Set the scale of the sprite according to the window size
    // TODO add the default window size in utils namespace
    sprite.scale(sf::Vector2f(window->getSize().x/800.f, window->getSize().y/600.f));

    // if it is a bullet do some moving of the sprite and only if it is not in control of itself
    if (entity->getType()=="bullet") {
        std::weak_ptr<EntityNS::Entity> fromShip = entity->getFrom();
        std::shared_ptr<sf::Sprite> spriteFrom;
        // Find the sprite to which we need to centre
        for (const auto& sprite: sprites) {
            if (sprite.first.get()==fromShip.lock().get()) {
                spriteFrom = sprite.second;
            }
        }

        double fromOffset = spriteFrom->getGlobalBounds().width/2.f;
        double bulletOffset = sprite.getGlobalBounds().width/2.f;
        double xOffset = fromOffset-bulletOffset;

        double yOffset;
        if (entity->getType()=="player") {
            yOffset = sprite.getGlobalBounds().height;
        }
        else {
            yOffset = -spriteFrom->getGlobalBounds().height;
        }

        // Change the location of the bullet by the offset
        sprite.move(sf::Vector2f(xOffset, -yOffset));
        // store it in the internal representation of the bullet
        // TODO make it more legible
        double xOffsetEntity =
                xOffset/window->getSize().x*(Utils::CoordinateBound::UPPER_X-Utils::CoordinateBound::LOWER_X);
        double yOffsetEntity =
                yOffset/window->getSize().y*(Utils::CoordinateBound::UPPER_Y-Utils::CoordinateBound::LOWER_Y);

        double xEntity = xOffsetEntity+entity->getPos()->getX();
        double yEntity = yOffsetEntity+entity->getPos()->getY();
        Utils::Position pos(xEntity, yEntity);
        entity->setPosition(pos);
    }

    return sprite;
}

std::string Draw::getType()
{
    return "draw";
}

bool Draw::isOpen() const
{
    return open;
}
