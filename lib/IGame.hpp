/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IGame.cpp
*/

#pragma once

class IGame {
public:
    virtual ~IGame() = default;
    virtual void run() = 0;
};
