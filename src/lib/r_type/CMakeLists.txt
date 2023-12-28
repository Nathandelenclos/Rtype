cmake_minimum_required(VERSION 3.25)
project(r-type-lib)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/lib/r_type/components src/lib/r_type/entities src/lib/r_type/services)
add_library(lib_r_type SHARED
        src/lib/r_type/RType.cpp
        src/lib/r_type/RType.hpp
        src/lib/r_type/services/Graphic.cpp
        src/lib/r_type/services/Graphic.hpp
        src/lib/r_type/entities/Player.cpp
        src/lib/r_type/entities/Player.hpp
        src/lib/r_type/components/Drawable.cpp
        src/lib/r_type/components/Drawable.hpp)

target_compile_options(lib_r_type PRIVATE -fPIC)

set_target_properties(lib_r_type PROPERTIES PREFIX "" SUFFIX .so LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
