/**
 * @file GameParser.cpp
 * @author Basil Rommens
 * @date 1/5/20
 * @brief The cpp file of the class GameParser
 */

#include "GameParser.h"
#include "Game.h"

std::vector<std::string> GameParser::parseGame(const std::string& gameFile)
{
    // Parse json file of the game
    std::ifstream i(gameFile);
    json j;
    i >> j;

    // add all the levels from the game json to the levels vector
    std::vector<std::string> levels{};
    for (const auto& levelFile: j["Levels"]) {
        levels.push_back(levelFile);
    }

    return levels;
}

// TODO add check for when entity is not a valid pointer
void GameParser::parseLevel(const std::string& levelFile)
{
    // Parse json file
    std::ifstream i(levelFile);
    json j;
    i >> j;

    // TODO make extra functions for applying the observer pattern
    parseWorld(j["World"]);
    parsePlayer(j["Player"]);
    parseEnemy(j["Enemies"]);
}

// TODO error on empty filename
void GameParser::parsePlayer(const std::string&& player)
{
    // Parse json file
    std::ifstream i(player);
    json j;
    i >> j;

    // TODO if type is a mismatch -> error
    std::string image = j["Image"];
    Utils::Position position(j["xPos"], j["yPos"]);
    double HP = j["HP"];
    double HSpeed = j["HSpeed"];
    Utils::Hitbox hitbox(j["Hitbox"]["Width"], j["Hitbox"]["Height"]);

    std::shared_ptr<Model::Entity> playerShip(
            new Model::PlayerShip(image, position, HP, HSpeed, 20, hitbox, game->world));
    playerShip->addBullet(createBullet(j["Bullet"], playerShip));
    game->world.addEntity(playerShip);

    //playerShip->addWorld(world);

    std::shared_ptr<ObserverPattern::Observer> observerPlayer(playerShip);
    game->controller.addObserver(observerPlayer);
}

// TODO error on empty filename
void GameParser::parseEnemy(const std::string&& enemy)
{
    // Parse json file
    std::ifstream i(enemy);
    json j;
    i >> j;

    double HSpeed = j["HSpeed"];
    double VSpeed = j["VSpeed"];

    // TODO if type is a mismatch -> error
    for (auto ship: j["Ships"]) {
        std::string image = ship["Image"];
        Utils::Position position(ship["xPos"], ship["yPos"]);
        double HP = ship["HP"];

        Utils::Hitbox hitbox{ship["Hitbox"]["Width"], ship["Hitbox"]["Height"]};

        auto enemyShip = std::make_shared<Model::EnemyShip>(
                Model::EnemyShip(image, position, HP, HSpeed, 30, hitbox, VSpeed, game->world));

        enemyShip->addBullet(createBullet(ship["Bullet"], enemyShip));

        std::shared_ptr<Model::Entity> sharedEntity(enemyShip);
        game->world.addEntity(sharedEntity);

        std::shared_ptr<ObserverPattern::Observer> sharedObserver(enemyShip);
        game->controller.addObserver(sharedObserver);

        std::weak_ptr<Model::EnemyShip> weakEnemy = enemyShip;
        enemyShip->addShip(weakEnemy);

        //enemyShip->addWorld(world);
    }
}

void GameParser::parseWorld(const std::string& worldName)
{
    // Parse json file
    std::ifstream i(worldName);
    json j;
    i >> j;

    game->world = Model::World(j["Image"], j["End"]);
}

std::shared_ptr<Model::Bullet>
GameParser::createBullet(const std::string& fileName, std::weak_ptr<Model::Entity> entity)
{
    // Parse json file
    std::ifstream i(fileName);
    json j;
    i >> j;

    Utils::Position position(entity.lock()->getHitbox().getWidth()/2, 0);
    std::string image = j["Image"];
    double damage = j["Damage"];
    double speed = j["Speed"];
    // TODO Clean up this mess
    Utils::Hitbox hitbox{j["Hitbox"]["Width"], j["Hitbox"]["Height"]};
    // Move the bullet so that it is centred over the entity
    position.moveXPos(-hitbox.getWidth()/2, hitbox);
    Utils::Direction direction{};
    // TODO fix y spawning
    if (entity.lock()->getType()=="enemy") {
        direction = Utils::Direction::DOWN;
        position.moveYPos(-entity.lock()->getHitbox().getHeight(), hitbox);
    }
    else if (entity.lock()->getType()=="player") {
        direction = Utils::Direction::UP;
        position.moveYPos(hitbox.getHeight(), hitbox);
    }
    return std::make_shared<Model::Bullet>(
            Model::Bullet(image, direction, speed, damage, position, entity, hitbox));
}

void GameParser::setGame(Game& newGame) const
{
    newGame.controller = game->controller;
    newGame.world = game->world;
}

GameParser::GameParser()
        :game(new Game) { }
