cmake_minimum_required(VERSION 3.15)
project(Project-Space-Invaders)

SET(CMAKE_CXX_STANDARD 14)

add_executable(Project-Space-Invaders
        src/main.cpp
        src/Entity/Entity.cpp
        src/Entity/Ship.cpp
        src/Entity/PlayerShip.cpp
        src/Entity/EnemyShip.cpp
        src/Entity/Bullet.cpp
        src/Entity/World.cpp
        src/Entity/BGTile.cpp
        src/main.cpp
        src/Entity/Position.cpp
        src/Game.cpp
        src/utils/Stopwatch.cpp
        src/utils/Transformation.cpp)


target_link_libraries(Project-Space-Invaders "-lsfml-graphics -lsfml-window -lsfml-system")

add_executable(test src/testMain.cpp src/utils/Stopwatch.cpp src/utils/Transformation.cpp)
target_link_libraries(test "-lsfml-graphics -lsfml-window -lsfml-system")