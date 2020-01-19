/**
 * @file Game.cpp
 * @author Basil Rommens
 * @date 01/12/2019
 * @brief The cpp file of the class Game
 */

#include "Game.h"
#include "Parser/GameParser.h"

// set the instance of the Stopwatch to nullptr to be not pointing to anything
std::shared_ptr<Utils::Stopwatch> Utils::Stopwatch::instance = nullptr;

void Game::start(const std::vector<std::string>& levels)
{
        sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Project Space Invaders");
        bool replay;
        // construct gameparser with this game as a default
        GameParser gameParser{*this};

        do {
                bool failure = false;

                for (const auto& level : levels) {
                        // Parse the level and then set all the parsed elements on the current game
                        gameParser.parseLevel(level);

                        failure = play(renderWindow);
                        if (failure) {
                                break;
                        }
                        if (not renderWindow.isOpen()) {
                                break;
                        }
                }

                // end the game if no window is open
                if (not renderWindow.isOpen()) {
                        break;
                }
                // TODO try to do this inside loop to restart game: fix error when lost

                if (failure) { // display lost message
                        displayLost(renderWindow);
                } // otherwise you have won
                else {
                        displayWon(renderWindow);
                }

                replay = controller.replay(renderWindow);
                renderWindow.clear();
        } while (renderWindow.isOpen() and replay);
        // Downcast worldObserver
        std::shared_ptr<Model::World> world = std::static_pointer_cast<Model::World>(worldObserver);

        this->controller.clearObservers();
}

bool Game::play(sf::RenderWindow& renderWindow)
{
        bool failure = false;

        // Downcast worldObserver
        std::shared_ptr<Model::World> world = std::static_pointer_cast<Model::World>(worldObserver);

        std::shared_ptr<sf::RenderWindow> window(&renderWindow);
        std::shared_ptr<View::Draw> draw(new View::Draw(window, world));
        std::shared_ptr<ObserverPattern::Observer> drawShared(draw);

        // add draw object to the worldObserver because it enables to spawn bullets
        world->addObserver(drawShared);

        // Add the the observer to each of the dummy bullets of the players/enemies
        for (const std::shared_ptr<Model::Entity> entity : world->getEntities()) {
                if (entity->getType() == "enemy" or entity->getType() == "player") {
                        std::shared_ptr<Model::Bullet> bullet = entity->getDummyBullet();
                        bullet->addObserver(drawShared);
                }
        }

        // Add the draw object to each class
        for (const std::shared_ptr<Model::Entity> entity : world->getEntities()) {
                entity->addObserver(drawShared);
        }

        // Add the worldObserver to the controller for observation in order to apply collision detection
        controller.addObserver(worldObserver);

        // run the program as long as the window is open
        while (renderWindow.isOpen()) {
                // start the timing of the stopwatch
                stopwatch->start();

                /// Part of control
                // handles the collisions and player input
                controller.handleInput(renderWindow, world);
                // updates the world
                controller.update(world);

                /// Part of view
                // if the window has been closed then exit the level
                if (not draw->isOpen()) {
                        break;
                }
                // if the player has been destroyed or the enemies hit the endLine
                if (not world->hasPlayer() or world->isEnd()) {
                        failure = true;
                        break;
                }
                // if there are no enemies left in space
                if (not world->hasEnemies()) {
                        break;
                }
                draw->view();

                wait();
        }

        worldObserver.reset();
        controller.clearObservers();
        return failure;
}

void Game::wait() const
{
        int elapsedTime = floor(stopwatch->get_lap().count() * Utils::count);
        if (elapsedTime < Utils::frameDuration) {
                // multiplied by 100 cause framerate doesnt seem right
                usleep(Utils::frameDuration - elapsedTime);
        }
}

// TODO move this function elsewhere cause it doesnt belong here
void Game::displayLost(sf::RenderWindow& renderWindow) const { displayText("Game Over", renderWindow); }

void Game::displayWon(sf::RenderWindow& renderWindow) const { displayText("Victory", renderWindow); }

void Game::displayText(const std::string& textToDisplay, sf::RenderWindow& renderWindow) const
{
        // This function returns whenever the renderWindow is closed
        if (not renderWindow.isOpen()) {
                return;
        }
        sf::Text text;

        sf::Font font;

        if (!font.loadFromFile(Utils::font)) {
                throw std::runtime_error("Failed to load font");
        }

        // select the font
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString(textToDisplay);

        // set the character size
        text.setCharacterSize(60); // in pixels, not points!

        // set the color
        text.setColor(sf::Color::White);
        text.setPosition(renderWindow.getSize().x / 2.f, 0.f);

        renderWindow.clear();
        renderWindow.draw(text);
        renderWindow.display();
}
