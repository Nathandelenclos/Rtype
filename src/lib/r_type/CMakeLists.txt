cmake_minimum_required(VERSION 3.25)
project(r-type-lib)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/lib/r_type/components src/lib/r_type/entities src/lib/r_type/services)
add_library(lib_r_type SHARED
        src/lib/r_type/RType.cpp
        src/lib/r_type/RType.hpp
        src/lib/r_type/services/Graphic.cpp
        src/lib/r_type/services/Graphic.hpp
        #src/lib/r_type/entities/Player.cpp
        #src/lib/r_type/entities/Player.hpp
        src/lib/r_type/components/Drawable.cpp
        src/lib/r_type/components/Drawable.hpp
        src/lib/r_type/components/Animatable.cpp
        src/lib/r_type/components/Animatable.hpp
        networking/server/ServerSocket.cpp
        networking/server/ServerSocket.hpp
        src/lib/r_type/Scenes/IScene.hpp
        src/lib/r_type/Scenes/AScene.cpp
        src/lib/r_type/Scenes/AScene.hpp
        src/lib/r_type/components/IComponent.hpp
        src/lib/r_type/Scenes/Lobby/Lobby.cpp
        src/lib/r_type/Scenes/Lobby/Lobby.hpp
        src/lib/r_type/services/IService.hpp
        src/lib/r_type/services/AService.cpp
        src/lib/r_type/services/Animation.hpp
        src/lib/r_type/services/Animation.cpp
        src/lib/r_type/services/AService.hpp
        src/lib/r_type/entities/IEntity.hpp
        src/lib/r_type/services/Collision.cpp
        src/lib/r_type/services/Collision.hpp
        src/lib/r_type/services/Move.cpp
        src/lib/r_type/services/Move.hpp
        src/lib/r_type/components/Timer.cpp
        src/lib/r_type/components/Timer.hpp
        src/lib/r_type/services/TimeManagement.cpp
        src/lib/r_type/services/TimeManagement.hpp)


if (UNIX OR APPLE)
    include(FetchContent)
    FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.x)
    FetchContent_MakeAvailable(SFML)
    target_link_libraries(lib_r_type PRIVATE sfml-graphics sfml-audio sfml-system sfml-window -fPIC -g)

endif (UNIX OR APPLE)

set_target_properties(lib_r_type PROPERTIES PREFIX "" SUFFIX .so LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
