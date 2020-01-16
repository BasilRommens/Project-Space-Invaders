/**
 * @file GameParser.h
 * @author Basil Rommens
 * @date 1/5/20
 * @brief The header file of the class GameParser
 */

#ifndef PROJECT_SPACE_INVADERS_GAMEPARSER_H
#define PROJECT_SPACE_INVADERS_GAMEPARSER_H

#include <string>
#include <vector>
#include <fstream>

#include "utils/json.hpp"
#include "Model/World.h"
#include "Model/PlayerShip.h"
#include "Model/EnemyShip.h"
#include "bad_type.h"
#include "bad_file.h"

using json = nlohmann::json;

class Game;

class GameParser {
private:
    Game& game; ///< The current game that will be parsed

    /**
     * @brief Loads the player from a string given with it
     * @param player: The filename which to parse
     */
    void parsePlayer(const std::string&& player);

    /**
     * @brief Loads the enemy from a string given to it
     * @param enemy: The filename which to parse
     */
    void parseEnemy(const std::string&& enemy);

    /**
     * @brief Loads the world from a string given to it
     * @param worldName: The filename of the world to parse
     */
    void parseWorld(const std::string& worldName);

    /**
     * @brief The bullet that is used to shoot from one of the ships
     * @param fileName: The name of the file from where to parse the bullets
     * @param entity: The name of the entity from which the bullet supposedly comes
     * @return The bullet in a shared ptr type
     * TODO add a check if the weakptr is valid
     * TODO add a check if the filename is valid
     */
    std::shared_ptr<Model::Bullet> createBullet(const std::string& fileName, std::weak_ptr<Model::Entity> entity);

public:
    /**
     * @brief The default constructor of the class GameParser
     */
    GameParser(Game& game);

    /**
     * @brief Parses a single level file
     * @param levelFile: The filename of the level
     */
    void parseLevel(const std::string& levelFile);

    /**
     * @brief Parses the 'game' by only returning the level files
     * @param gameFile: The file name of the game to parse
     * @return The names of the level files in order
     */
    std::vector<std::string> parseGame(const std::string& gameFile);
};

#endif //PROJECT_SPACE_INVADERS_GAMEPARSER_H
