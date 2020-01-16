/**
 * @file GameParser.cpp
 * @author Basil Rommens
 * @date 1/5/20
 * @brief The cpp file of the class GameParser
 */

#include "GameParser.h"
#include "Game.h"

GameParser::GameParser(Game& game)
        :game(game) { }

std::vector<std::string> GameParser::parseGame(const std::string& gameFile)
{
    // Parse json file of the game
    std::ifstream i(gameFile);
    json j;
    i >> j;

    // TODO make throw clearer
    if (j["Type"]!="game") {
        throw Exception::bad_type("The type of the file doesnt match that one of the game");
    }

    // TODO add exception handling over here
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

    // TODO make throw clearer
    if (j["Type"]!="level") {
        throw;
    }

    // TODO make extra functions for applying the observer pattern
    try {
        parseWorld(j["World"]);
        parsePlayer(j["Player"]);
        parseEnemy(j["Enemies"]);
    }
    catch (const Exception::bad_type& e) {
        std::cout << e.what() << std::endl;
        throw Exception::bad_type("One of the files couldnt be parsed due to being the wrong type");
    }
    catch (const Exception::entity_underflow& e) {
        std::cout << e.what() << std::endl;
        throw Exception::bad_file("One of the files couldnt be parsed correctly");
    }
}

// TODO error on empty filename
void GameParser::parsePlayer(const std::string&& player)
{
    // Parse json file
    std::ifstream i(player);
    json j;
    i >> j;

    if (j["Type"]!="player") {
        throw Exception::bad_type("The type of the player file is wrong");
    }

    // downcast the world to the right type to have the right functions at hand
    std::shared_ptr<Model::World> world = std::static_pointer_cast<Model::World>(game.worldObserver);

    // TODO
    try {
        std::string image = j["Image"];
        Utils::Position position(j["xPos"], j["yPos"]);
        double HP = j["HP"];
        double HSpeed = j["HSpeed"];
        Utils::Hitbox hitbox(j["Hitbox"]["Width"], j["Hitbox"]["Height"]);

        std::shared_ptr<Model::Entity> playerShip(
                new Model::PlayerShip(image, position, HP, HSpeed, 20, hitbox, *world));
        playerShip->addBullet(createBullet(j["Bullet"], playerShip));
        world->addEntity(playerShip);

        std::shared_ptr<ObserverPattern::Observer> observerPlayer(playerShip);
        game.controller.addObserver(observerPlayer);
    }
    catch (const json::exception& e) {
        std::cout << e.what() << std::endl;
        throw Exception::bad_file("The file of the player doesnt seem to have the correct attributes");
    }
    catch (const Exception::bad_type& e) {
        std::cout << e.what() << std::endl;
        throw Exception::bad_file("The file of the player doesnt seem to have the correct attributes");
    }
}

// TODO error on empty filename
void GameParser::parseEnemy(const std::string&& enemy)
{
    // Parse json file
    std::ifstream i(enemy);
    json j;
    i >> j;

    // TODO make throw clearer
    if (j["Type"]!="enemy") {
        throw Exception::bad_type("The type of the enemy file is wrong");
    }

    // downcast the world to the right type to have the right functions at hand
    std::shared_ptr<Model::World> world = std::static_pointer_cast<Model::World>(game.worldObserver);

    try {
        double HSpeed = j["HSpeed"];
        double VSpeed = j["VSpeed"];

        int initialEntityCount = world->getEntities().size();

        // TODO if type is a mismatch -> error
        for (auto ship: j["Ships"]) {
            try {
                std::string image = ship["Image"];
                Utils::Position position(ship["xPos"], ship["yPos"]);
                double HP = ship["HP"];

                Utils::Hitbox hitbox{ship["Hitbox"]["Width"], ship["Hitbox"]["Height"]};

                auto enemyShip = std::make_shared<Model::EnemyShip>(
                        Model::EnemyShip(image, position, HP, HSpeed, 30, hitbox, VSpeed, *world));

                enemyShip->addBullet(createBullet(ship["Bullet"], enemyShip));

                std::shared_ptr<Model::Entity> sharedEntity(enemyShip);
                world->addEntity(sharedEntity);

                std::shared_ptr<ObserverPattern::Observer> sharedObserver(enemyShip);
                game.controller.addObserver(sharedObserver);

                std::weak_ptr<Model::EnemyShip> weakEnemy = enemyShip;
                enemyShip->addShip(weakEnemy);
            }
            catch (const json::exception& e) {
                std::cerr << e.what() << std::endl;
                std::cerr << "One of the attributes that an enemy needed wasn't available in the json file"
                          << std::endl;
                continue; // nothing has been added so we can continue
            }
            catch (const Exception::bad_type& e) {
                std::cerr << e.what() << std::endl;
                std::cout << "The enemy couldn't be created" << std::endl;
                continue;
            }
        }
        // Error because no enemies were created and therefore no level can be constructed (it is instantly won)
        if (world->getEntities().size()-initialEntityCount==0) {
            throw Exception::entity_underflow("No enemies were created");
        }
    }
    catch (const json::exception& e) {
        std::cout << e.what() << std::endl;
        throw Exception::bad_file("The enemy type file wasnt correct");
    }

}

void GameParser::parseWorld(const std::string& worldName)
{
    // Parse json file
    std::ifstream i(worldName);
    json j;
    i >> j;

    // TODO make throw clearer
    if (j["Type"]!="world") {
        throw Exception::bad_type("The type of the world file is wrong");
    }

    game.worldObserver = std::make_shared<Model::World>(Model::World(j["Image"], j["End"]));
}

std::shared_ptr<Model::Bullet>
GameParser::createBullet(const std::string& fileName, std::weak_ptr<Model::Entity> entity)
{
    // Parse json file
    std::ifstream i(fileName);
    json j;
    i >> j;

    // TODO make throw clearer
    if (j["Type"]!="bullet") {
        throw Exception::bad_type("The type of the bullet file is wrong");
    }

    try {
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
        else {
            throw Exception::bad_type("The type to which the bullet is supposed to bind is not correct");
        }

        return std::make_shared<Model::Bullet>(
                Model::Bullet(image, direction, speed, damage, position, entity, hitbox));
    }
    catch (const json::exception& e) {
        std::cout << e.what() << std::endl;
        throw Exception::bad_file("The file that contains bullet cant be correctly parsed");
    }
}
