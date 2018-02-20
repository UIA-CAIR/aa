cmake_minimum_required(VERSION 2.8.7)
project(AA)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_LIST_DIR}/cmake)


set(SOURCE_FILES
        src/game/Game.cpp
        src/game/Game.h
        src/main.cpp
        src/Dice.cpp
        src/Dice.h
        src/battlesim/Battlesim.cpp
        src/battlesim/Battlesim.h
        src/Board.cpp
        src/Board.h
        src/util/matrix.cpp
        src/util/matrix.h
        )


add_executable(AA ${SOURCE_FILES})