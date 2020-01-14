cmake_minimum_required(VERSION 3.10)
project(Project-Space-Invaders)

SET(CMAKE_CXX_STANDARD 14)

add_executable(Project-Space-Invaders
        src/main.cpp
        src/Model/Entity.cpp
        src/Model/Ship.cpp
        src/Model/PlayerShip.cpp
        src/Model/EnemyShip.cpp
        src/Model/Bullet.cpp
        src/Model/World.cpp
        src/utils/Position.cpp
        src/utils/Stopwatch.cpp
        src/utils/Transformation.cpp
        src/utils/Event.h
        src/Game.cpp
        src/utils/ObserverPattern/Subject.cpp
        src/utils/ObserverPattern/Observer.cpp
        src/View/Draw.cpp
        src/utils/json.hpp
        src/Control/Controller.cpp
        src/utils/Hitbox.cpp
        src/GameParser.cpp)


target_link_libraries(Project-Space-Invaders "-lsfml-graphics -lsfml-window -lsfml-system")