cmake_minimum_required(VERSION 3.15)
project(Project-Space-Invaders)

SET(CMAKE_CXX_STANDARD 11)

add_executable(Project-Space-Invaders
        main.cpp
        src/Entity.cpp
        src/Ship.cpp
        src/PlayerShip.cpp
        src/EnemyShip.cpp
        src/Bullet.cpp
        src/World.cpp
        src/BGTile.cpp)