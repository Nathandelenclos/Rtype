/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

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

    /**
     * @brief ClientCore, constructor of ClientCore
     */
    ClientCore();

    /**
     * @brief ~ClientCore, destructor of ClientCore
     */
    ~ClientCore() = default;

    /**
     * @brief init_socket, init the socket
     *
     * @param ip
     * @param port
     * @return true if the socket is init
     */
    bool init_socket(const std::string &ip, int port);

    /**
     * @brief run, run the client
     */
    void run();

    /**
     * @brief getSocket, get the socket
     *
     * @return std::shared_ptr<ClientSocket>
     */
    std::shared_ptr<IScene> getSceneByName(const std::string &name);

    /**
     * @brief setCurrentScene, set the current scene
     *
     * @param name
     */
    void setCurrentScene(const std::string &name);

    /**
     * @brief getCurrentScene, get the current scene
     *
     * @return std::shared_ptr<IScene>
     */
    std::shared_ptr<IScene> getCurrentScene() const;

    /**
     * @brief sendHeartBeat, send the heart beat
     *
     * @param window
     */
    void sendHeartBeat(sf::RenderWindow &window);

    /**
     * @brief startHeartBeat, start the heart beat
     */
    void startHeartBeat();

  private:
    std::shared_ptr<ClientSocket> _socket;
    sf::RenderWindow _window;
    std::map<std::string, std::shared_ptr<IScene>> _scenes;
    std::shared_ptr<IScene> _currentScene;
    std::thread _heartBeatThread;
};
