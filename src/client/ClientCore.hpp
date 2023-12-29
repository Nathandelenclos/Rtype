//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <map>
#include "../../networking/client/ClientSocket.hpp"
#include "Scenes/IScene.hpp"
#include "Scenes/Menu/MenuScene.hpp"
#include "Scenes/Menu/MainScene.hpp"

class ClientCore {
    public:
        ClientCore();
        ~ClientCore() = default;

        bool init_socket(const std::string& ip, int port);

        void run();

        std::shared_ptr<IScene> getSceneByName(const std::string& name);
        void setCurrentScene(const std::string& name);

    private:
        std::shared_ptr<ClientSocket> _socket;
        std::map<std::string, std::shared_ptr<IScene>> _scenes;
        std::shared_ptr<IScene> _currentScene;
};
