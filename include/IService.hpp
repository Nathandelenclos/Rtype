/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IObject.hpp
*/

#pragma once

#include <vector>
#include "IObject.hpp"
#include "IGame.hpp"

class IGame;

class IService {
public:
    virtual void update(IGame *game, std::vector<IObject*> objects) = 0;
};
