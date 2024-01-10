//
// Created by talleux on 1/4/24.
//

#pragma once

#include "../AScene.hpp"
#include "../components/Drawable.hpp"
#include <SFML/Window/Keyboard.hpp>


class LobbyScene : public AScene {
    public:
        explicit LobbyScene(std::shared_ptr<ServerSocket> serverSocket);
        ~LobbyScene() override = default;

        void initScene();

        void update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet) override;

        void initEntities();
        void initServices();

    private:
        timeval _chrono;
        std::shared_ptr<Event> _lastEvent;
};
