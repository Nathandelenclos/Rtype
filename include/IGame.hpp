/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IGame.cpp
*/

#pragma once

#include "networking/shared/USocket.hpp"
#include <memory>
#include <vector>

class IService;

class IGame
{
  public:
    virtual ~IGame() = default;

    virtual void update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet) = 0;
};
