//
// Created by Talleux on 28/12/2023.
//

#include "ClientCore.hpp"

ClientCore::ClientCore()
{
    _socket = std::make_shared<ClientSocket>();
    _scenes["menu"] = std::make_unique<MenuScene>(this, _socket);
    _scenes["main"] = std::make_unique<MainScene>(this, _socket);
    _scenes["game"] = std::make_unique<GameScene>(this, _socket);
    _currentScene = _scenes["main"];
}

bool ClientCore::init_socket(const std::string& ip, int port)
{
    if (_socket->isInit())
        return true;
    bool init = _socket->init_client(ip, port);
    if (!init)
        return false;
    return init;
}

void ClientCore::run()
{
    _window.create(sf::VideoMode(800, 600), "R-Type");
    sf::Event event{};

    while (_window.isOpen()) {
        _window.clear();
        _socket->init_fd_set();
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();
            _currentScene->handleEvent(event, _window);
        }
        _currentScene->receiveData();
        _currentScene->update();
        _currentScene->display(_window);
        _window.display();
    }
    if (_heartBeatThread.joinable())
        _heartBeatThread.join();
}

std::shared_ptr<IScene> ClientCore::getSceneByName(const std::string& name)
{
    return _scenes[name];
}

void ClientCore::setCurrentScene(const std::string& name)
{
    _currentScene->continueScene = false;
    _currentScene->pauseScene();
    _currentScene = getSceneByName(name);
    _currentScene->continueScene = true;
    _currentScene->resumeScene();
}

void ClientCore::sendHeartBeat(sf::RenderWindow& window)
{
    std::unique_ptr<Packet> packet = std::make_unique<Packet>();

    packet->code = HEARTBEAT;
    packet->data_size = sizeof(timeval);
    packet->data = malloc(packet->data_size);
    while (window.isOpen()) {
        gettimeofday((timeval*)packet->data, nullptr);
        _socket->send(packet.get(), _socket->serv_addr);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

std::shared_ptr<IScene> ClientCore::getCurrentScene() const
{
    return _currentScene;
}

void ClientCore::startHeartBeat()
{
    _heartBeatThread = std::thread(&ClientCore::sendHeartBeat, this, std::ref(_window));
}
