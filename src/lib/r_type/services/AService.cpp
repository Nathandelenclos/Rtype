//
// Created by talleux on 1/4/24.
//

#include "AService.hpp"

#include <utility>

AService::AService(std::shared_ptr<ServerSocket> serverSocket)
{
    _serverSocket = std::move(serverSocket);
}
