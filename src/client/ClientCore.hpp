//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <map>
#include <memory>
#include <chrono>
#include <thread>
#include <sys/time.h>
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

        void sendHeartBeat(sf::RenderWindow& window);


    private:
        std::shared_ptr<ClientSocket> _socket;
        sf::RenderWindow _window;
        std::map<std::string, std::shared_ptr<IScene>> _scenes;
        std::shared_ptr<IScene> _currentScene;
        std::thread _heartBeatThread;
};
