cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_REQUIRED ON)

project(minusculo)
add_executable(minusculo src/Main.cpp src/Game.cpp src/ResourceHolder.cpp)
target_include_directories(minusculo
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    /usr/include/SFML )
target_link_libraries(minusculo sfml-system sfml-window sfml-graphics)
