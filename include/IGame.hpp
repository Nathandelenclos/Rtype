/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IGame.cpp
*/

#pragma once

#include <vector>
#include <memory>
#include "networking/shared/USocket.hpp"

class IService;

class IGame {
public:
    virtual ~IGame() = default;

    virtual void update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet, int id) = 0;
};
