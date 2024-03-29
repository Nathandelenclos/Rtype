/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Server.hpp
*/

#pragma once

#include "../../networking/server/ServerSocket.hpp"
#include "DLLoader.hpp"
#include "IGame.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

class Server
{
  public:

    /**
     * @brief Construct a new Server:: Server object
     * @param port
     */
    Server(int port);

    /**
     * @brief Destroy the Server:: Server object
     */
    ~Server() = default;
    void run();

  private:
    std::unique_ptr<DLLoader> _gameLoader;
    std::unique_ptr<IGame> _game;
    std::shared_ptr<ServerSocket> _serverSocket;
    std::shared_ptr<Packet> _packet;
    std::tuple<std::unique_ptr<Packet>, int> _packetClientId;
    std::unique_ptr<Packet> _packetHeartBeat;
    timeval _receveidTime{};
    timeval _currentTime{};
    timeval _packetHeartBeatData{};
};
