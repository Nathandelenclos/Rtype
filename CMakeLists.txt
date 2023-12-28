cmake_minimum_required(VERSION 3.25)
project(r-type)

set(CMAKE_CXX_STANDARD 17)

include(src/lib/r_type/CMakeLists.txt)

add_executable(r-type_server
        src/lib/IGame.hpp
        src/lib/DLLoader.hpp
        src/lib/IObject.hpp
        src/lib/IService.hpp
        src/server/main.cpp)

find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)
add_executable(r-type_client
        src/client/main.cpp)
target_link_libraries(r-type_client sfml-graphics sfml-audio sfml-system sfml-window)

set_target_properties(r-type_server PROPERTIES EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set_target_properties(r-type_client PROPERTIES EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
