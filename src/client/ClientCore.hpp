//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include "Scenes/Game/GameScene.hpp"
#include "Scenes/IScene.hpp"
#include "Scenes/Menu/MainScene.hpp"
#include "Scenes/Menu/MenuScene.hpp"
#include "networking/client/ClientSocket.hpp"
#include <chrono>
#include <map>
#include <memory>
#include <sys/time.h>
#include <thread>

class ClientCore
{
  public:
    ClientCore();
    ~ClientCore() = default;

    bool init_socket(const std::string &ip, int port);

    void run();

    std::shared_ptr<IScene> getSceneByName(const std::string &name);
    void setCurrentScene(const std::string &name);
    std::shared_ptr<IScene> getCurrentScene() const;

    void sendHeartBeat(sf::RenderWindow &window);
    void startHeartBeat();

  private:
    std::shared_ptr<ClientSocket> _socket;
    sf::RenderWindow _window;
    std::map<std::string, std::shared_ptr<IScene>> _scenes;
    std::shared_ptr<IScene> _currentScene;
    std::thread _heartBeatThread;
};
