//
// Created by Talleux on 28/12/2023.
//

#include "ClientCore.hpp"

ClientCore::ClientCore()
{
    _socket = std::make_shared<ClientSocket>();
    _scenes["menu"] = std::make_unique<MenuScene>(_socket);
    _currentScene = std::move(_scenes["menu"]);
}

bool ClientCore::init_socket(const std::string& ip, int port)
{
    return _socket->init_client(ip, port);
}

void ClientCore::run()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "R-Type");
    sf::Event event{};

    while (window.isOpen()) {
        window.clear();
        _socket->init_fd_set();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            _currentScene->handleEvent(event, window);
        }
        _currentScene->receiveData();
        _currentScene->update();
        _currentScene->display(window);
        window.display();
    }
}
