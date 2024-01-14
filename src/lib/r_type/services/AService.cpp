//
// Created by talleux on 1/4/24.
//

#include "AService.hpp"

#include <utility>

/**
 * @brief Construct a new AService:: AService object
 * @param serverSocket
 */
AService::AService(std::shared_ptr<ServerSocket> serverSocket)
{
    _serverSocket = std::move(serverSocket);
}
