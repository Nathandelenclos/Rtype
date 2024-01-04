/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Server.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <functional>
#include "IGame.hpp"
#include "DLLoader.hpp"
#include "../../networking/server/ServerSocket.hpp"

class Server {
public:
    Server(std::string const& ip, int port);
    ~Server() = default;
    void run();

private:
    std::unique_ptr<DLLoader> _gameLoader;
    std::unique_ptr<IGame> _game;
    std::shared_ptr<ServerSocket> _serverSocket;
    std::unique_ptr<Packet> _packet;
    std::tuple<std::unique_ptr<Packet>, int> _packetClientId;
    std::unique_ptr<Packet> _packetHeartBeat;
    timeval _receveidTime{};
    timeval _currentTime{};
    timeval _packetHeartBeatData{};
};
