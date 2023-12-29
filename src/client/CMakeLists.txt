cmake_minimum_required(VERSION 3.25)
project(r-type-client)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

add_executable(r-type_client
        src/client/main.cpp
        networking/client/ClientSocket.cpp
        networking/client/ClientSocket.hpp
        src/client/ClientCore.cpp
        src/client/ClientCore.hpp
        src/client/Scenes/IScene.hpp
        src/client/Components/IComponent.hpp
        src/client/Components/AComponent.cpp
        src/client/Components/AComponent.hpp
        src/client/Components/Text/TextComponent.cpp
        src/client/Components/Text/TextComponent.hpp
        src/client/Scenes/AScene.cpp
        src/client/Scenes/AScene.hpp
        src/client/Scenes/Menu/MenuScene.cpp
        src/client/Scenes/Menu/MenuScene.hpp
        src/client/Components/Button/ButtonComponent.cpp
        src/client/Components/Button/ButtonComponent.hpp
        src/client/Components/Input/InputComponent.cpp
        src/client/Components/Input/InputComponent.hpp
        src/client/Components/Sound/SoundComponent.cpp
        src/client/Components/Sound/SoundComponent.hpp
        src/client/Components/Music/MusicComponent.cpp
        src/client/Components/Music/MusicComponent.hpp
        src/client/Scenes/Menu/MainScene.cpp
        src/client/Scenes/Menu/MainScene.hpp
        src/client/Components/Sprite/SpriteComponent.cpp
        src/client/Components/Sprite/SpriteComponent.hpp)
target_link_libraries(r-type_client sfml-graphics sfml-audio sfml-system sfml-window)

set_target_properties(r-type_client PROPERTIES EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
