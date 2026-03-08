cmake_minimum_required(VERSION 4.2)
project(CACL)

set(CMAKE_CXX_STANDARD 14)

add_executable(CACL
        src/main.cpp
        src/Player.cpp
        src/TicTacToe.cpp
        src/Board.cpp
)

add_executable(server src/Server.cpp
)

add_executable(client src/Client.cpp
)

set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

target_compile_options(server PRIVATE -lpthread)
target_compile_options(client PRIVATE -lpthread)


target_include_directories(CACL PRIVATE include)