/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IObject.hpp
*/

#pragma once

#include "IGame.hpp"
#include "IObject.hpp"
#include <vector>

class IGame;

class IService
{
  public:
    virtual void update(IGame *game, std::vector<IObject *> objects) = 0;
};
