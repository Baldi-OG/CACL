cmake_minimum_required(VERSION 4.2)
project(CACL)

set(CMAKE_CXX_STANDARD 14)

add_executable(CACL
        src/main.cpp
        src/Player.cpp
        src/TicTacToe.cpp
        src/Board.cpp
)

target_include_directories(CACL PRIVATE include)