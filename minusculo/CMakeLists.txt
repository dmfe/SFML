cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-DNDEBUG")

project(minusculo VERSION 1.0)

find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(minusculo ${SRC_FILES})
target_include_directories(minusculo PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(minusculo PRIVATE
  sfml-graphics sfml-window sfml-system sfml-audio sfml-network
)


