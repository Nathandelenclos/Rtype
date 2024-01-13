//
// Created by Talleux on 28/12/2023.
//

#include "ClientCore.hpp"

/**
 * @brief Construct a new Client Core:: Client Core object
 *
 */
ClientCore::ClientCore()
{
    _socket = std::make_shared<ClientSocket>();
    _scenes["menu"] = std::make_unique<MenuScene>(this, _socket);
    _scenes["main"] = std::make_unique<MainScene>(this, _socket);
    _scenes["game"] = std::make_unique<GameScene>(this, _socket);
    _currentScene = _scenes["main"];
}

/**
 * @brief init_socket, initialize the socket with the ip and the port
 *
 * @param ip
 * @param port
 */
bool ClientCore::init_socket(const std::string &ip, int port)
{
    if (_socket->isInit())
        return true;
    bool init = _socket->init_client(ip, port);
    if (!init)
        return false;
    return init;
}

/**
 * @brief run, run the client
 *
 */
void ClientCore::run()
{
    _window.create(sf::VideoMode(800, 600), "R-Type");
    sf::Event event{};

    _window.setFramerateLimit(120);

    while (_window.isOpen()) {
        _window.clear();
        _socket->init_fd_set();
        _currentScene->handleEvent(event, _window);
        _currentScene->receiveData();
        _currentScene->update();
        _currentScene->display(_window);
        _window.display();
    }
    if (_heartBeatThread.joinable())
        _heartBeatThread.join();
}

/**
 * @brief getSceneByName, get the scene by name
 *
 * @param name
 * @return std::shared_ptr<IScene>
 */
std::shared_ptr<IScene> ClientCore::getSceneByName(const std::string &name)
{
    return _scenes[name];
}

/**
 * @brief setCurrentScene, set the current scene
 *
 * @param name
 */
void ClientCore::setCurrentScene(const std::string &name)
{
    _currentScene->continueScene = false;
    _currentScene->pauseScene();
    _currentScene = getSceneByName(name);
    _currentScene->continueScene = true;
    _currentScene->resumeScene();
}

/**
 * @brief sendHeartBeat, send the heart beat
 *
 * @param window
 */
void ClientCore::sendHeartBeat(sf::RenderWindow &window)
{
    std::unique_ptr<Packet> packet = std::make_unique<Packet>();

    packet->code = HEARTBEAT;
    packet->data_size = sizeof(timeval);
    packet->data = malloc(packet->data_size);
    while (window.isOpen()) {
        gettimeofday((timeval *)packet->data, nullptr);
        _socket->send(packet.get(), _socket->serv_addr);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    free(packet->data);
}

/**
 * @brief getCurrentScene, get the current scene
 *
 * @return std::shared_ptr<IScene>
 */
std::shared_ptr<IScene> ClientCore::getCurrentScene() const
{
    return _currentScene;
}

/**
 * @brief startHeartBeat, start the heart beat
 *
 */
void ClientCore::startHeartBeat()
{
    if (_heartBeatThread.joinable())
        _heartBeatThread.join();
    _heartBeatThread = std::thread(&ClientCore::sendHeartBeat, this, std::ref(_window));
}
