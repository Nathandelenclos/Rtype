/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RType.cpp
*/

#include "RType.hpp"

#include <utility>

extern "C" RType *create(std::shared_ptr<ServerSocket> socket)
{
    return new RType(std::move(socket));
}
