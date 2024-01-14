/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IObject.hpp
*/

#pragma once

#include "../networking/server/ServerSocket.hpp"
#include <cstring>
#include <memory>
#include <string>

class IObject
{
  public:
    virtual ~IObject() = default;
    virtual Packet *getPacket() = 0;
};
