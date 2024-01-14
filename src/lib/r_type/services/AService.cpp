/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

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
