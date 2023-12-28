cmake_minimum_required(VERSION 3.25)
project(r-type-server)

set(CMAKE_CXX_STANDARD 17)

add_executable(r-type_server
        src/server/main.cpp
        networking/server/ServerSocket.cpp
        networking/server/ServerSocket.hpp)

set_target_properties(r-type_server PROPERTIES EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
