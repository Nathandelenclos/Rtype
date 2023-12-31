/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RType.cpp
*/

#include "RType.hpp"

extern "C" RType* create(ServerSocket *socket) {
    return new RType(socket);
}
