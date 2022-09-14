cmake_minimum_required(VERSION 3.7)

project(Game)

find_package(SDL2 REQUIRED)
add_executable(Main src/Main.cpp)
target_link_libraries(Main ${SDL2_LIBRARIES})