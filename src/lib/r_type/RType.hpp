/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RType.hpp
*/

#pragma once

#include "./Scenes/IScene.hpp"
#include "./Scenes/Lobby/Lobby.hpp"
#include "./services/Graphic.hpp"
#include "IGame.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <utility>

class RType : public IGame
{
  public:

    /**
     * @brief Construct a new RType:: RType object
     * @param socket
     */
    explicit RType(std::shared_ptr<ServerSocket> socket)
    {
        _socket = std::move(socket);
        _scenes["Lobby"] = std::make_shared<LobbyScene>(_socket);
        _currentScene = nullptr;
        gettimeofday(&_broadcastGameState, nullptr);
    }

    /**
     * @brief Destroy the RType:: RType object
     */
    ~RType() override = default;

    /**
     * @brief update, update the game
     * @param event
     * @param packet
     */
    void update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet) override
    {
        timeval currentTime{};
        timeval elapsedTime{};
        gettimeofday(&currentTime, nullptr);
        timersub(&currentTime, &_broadcastGameState, &elapsedTime);

        if (!_socket->getClients().empty()) {
            if (_currentScene == nullptr) {
                _currentScene = _scenes["Lobby"];
                _currentScene->restartScene();
            }
        } else {
            _currentScene = nullptr;
        }

        if (_currentScene == nullptr)
            return;
        _currentScene->update(event, packet);

        if (_socket->getClients().size() != last_client_nb) {
            last_client_nb = _socket->getClients().size();
            std::shared_ptr<Packet> sendpacket = std::make_shared<Packet>();
            sendpacket->code = EVENT;
            sendpacket->data_size = strlen("new player");
            sendpacket->data = malloc(sendpacket->data_size);
            memcpy(sendpacket->data, "new player", sendpacket->data_size);
            _socket->broadcast(sendpacket.get());
        }

        if (elapsedTime.tv_sec >= 5) {
            _currentScene->broadcastGameState();
            gettimeofday(&_broadcastGameState, nullptr);
        }
    }

    std::shared_ptr<ServerSocket> _socket;
    std::map<std::string, std::shared_ptr<ISceneRType>> _scenes;
    std::shared_ptr<ISceneRType> _currentScene;
    float direction = 0.5;
    int last_client_nb = 0;
    timeval _broadcastGameState{};
};
