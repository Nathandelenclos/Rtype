/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RType.hpp
*/

#pragma once

#include <iostream>
#include <utility>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include "IGame.hpp"
#include "./services/Graphic.hpp"
#include "./Scenes/IScene.hpp"
#include "./Scenes/Lobby/Lobby.hpp"

class RType : public IGame {
public:
    explicit RType(std::shared_ptr<ServerSocket> socket) {
        _socket = std::move(socket);
        _scenes["Lobby"] = std::make_shared<LobbyScene>(_socket);
        _currentScene = _scenes["Lobby"];
    }

    ~RType() override = default;

    void update(std::shared_ptr<Event> event) override {
        _currentScene->update(event);

        if (_socket->getClients().size() != last_client_nb) {
            last_client_nb = _socket->getClients().size();
            std::shared_ptr<Packet> packet = std::make_shared<Packet>();
            packet->code = EVENT;
            packet->data_size = strlen("new player");
            packet->data = malloc(packet->data_size);
            memcpy(packet->data, "new player", packet->data_size);
            _socket->broadcast(packet.get());
        }

        _socket->checkClientsDeconnection();
    }

    std::shared_ptr<ServerSocket> _socket;
    std::map<std::string, std::shared_ptr<ISceneRType>> _scenes;
    std::shared_ptr<ISceneRType> _currentScene;
    float direction = 0.5;
    int last_client_nb = 0;
};
