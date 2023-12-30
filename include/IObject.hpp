/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IObject.hpp
*/

#pragma once

#include "../networking/shared/USocket.hpp"
#include "memory"

class IObject {
public:
    virtual ~IObject() = default;
    virtual Packet *getPacket() const = 0;
};
