cmake_minimum_required(VERSION 3.26)
project(bootstrap)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(bootstrap
        GameEngine.cpp
        GameEngine.hpp
        maintestdisplay.cpp)
target_link_libraries(bootstrap sfml-graphics sfml-audio)
