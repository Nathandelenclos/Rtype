cmake_minimum_required(VERSION 3.25)
project(r-type-server)

set(CMAKE_CXX_STANDARD 17)

add_executable(r-type_server
        src/server/main.cpp
        networking/server/ServerSocket.cpp
        networking/server/ServerSocket.hpp
        src/server/Server.cpp
        src/server/Server.hpp)

if (UNIX OR APPLE)
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
    target_link_libraries(r-type_server PRIVATE sfml-graphics sfml-audio sfml-system sfml-window)

endif (UNIX OR APPLE)

set_target_properties(r-type_server PROPERTIES EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
