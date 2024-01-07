//
// Created by talleux on 1/4/24.
//

#pragma once

#include "../AScene.hpp"
#include "../components/Drawable.hpp"


class LobbyScene : public AScene {
    public:
        explicit LobbyScene(std::shared_ptr<ServerSocket> serverSocket);
        ~LobbyScene() override = default;

        void initScene();

        void update(std::shared_ptr<Event> event) override;

        void initEntities();
        void initServices();

    private:
        timeval _chrono;
};
