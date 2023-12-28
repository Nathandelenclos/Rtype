/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IGame.cpp
*/

#pragma once

#include <vector>
#include "IObject.hpp"
#include "IService.hpp"

class IGame {
public:
    virtual ~IGame() = default;

    virtual std::vector<IObject*> getObjects() const = 0;
    virtual std::vector<IService*> getServices() const = 0;
};
