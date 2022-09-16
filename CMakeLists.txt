cmake_minimum_required(VERSION 3.7)

project(Game)

find_package(SDL2 REQUIRED)

add_executable(Main src/Main.cpp)
target_link_libraries(Main ${SDL2_LIBRARIES})
set_target_properties(Main PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)