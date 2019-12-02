cmake_minimum_required(VERSION 3.15)
project(Project-Space-Invaders)

SET(CMAKE_CXX_STANDARD 11)

add_executable(Project-Space-Invaders
        src/main.cpp
        src/Entity.cpp
        src/Ship.cpp
        src/PlayerShip.cpp
        src/EnemyShip.cpp
        src/Bullet.cpp
        src/World.cpp
        src/BGTile.cpp
        src/main.cpp
        src/Position.cpp
        src/Game.cpp)

add_executable(test src/testMain.cpp)

target_link_libraries(Project-Space-Invaders "-lsfml-graphics -lsfml-window -lsfml-system")
target_link_libraries(test "-lsfml-graphics -lsfml-window -lsfml-system")