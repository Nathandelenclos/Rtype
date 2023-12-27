cmake_minimum_required(VERSION 3.25)
project(r-type_server)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(r-type_server
        GameEngine.cpp
        GameEngine.hpp
        maintestdisplay.cpp
        lib/IGame.hpp
        lib/DLLoader.hpp)
target_link_libraries(r-type_server sfml-graphics sfml-audio)

add_library(test_lib_r_type SHARED
        lib/r_type/RType.cpp
        lib/r_type/RType.hpp
        lib/IGame.hpp)
target_compile_options(test_lib_r_type PRIVATE -fPIC)

set_target_properties(test_lib_r_type PROPERTIES PREFIX "" SUFFIX .so LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
