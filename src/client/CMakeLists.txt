cmake_minimum_required(VERSION 3.25)
project(r-type-client)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

add_executable(r-type_client
        src/client/main.cpp
        networking/client/ClientSocket.cpp
        networking/client/ClientSocket.hpp)
target_link_libraries(r-type_client sfml-graphics sfml-audio sfml-system sfml-window)

set_target_properties(r-type_client PROPERTIES EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
