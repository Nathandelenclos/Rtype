//
// Created by Talleux on 28/12/2023.
//

#include "ClientCore.hpp"

ClientCore::ClientCore()
{
    _socket = std::make_unique<ClientSocket>();
}

bool ClientCore::init_socket(std::string ip, int port)
{
    return _socket->init_client(ip, port);
}
