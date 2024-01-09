/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Player.hpp
*/

#pragma once

#include <iostream>
#include "IObject.hpp"
#include "Drawable.hpp"

class Player: public Drawable, public IObject {
public:
    explicit Player(ServerSocket *socket);
    ~Player() override = default;
    [[nodiscard]] Packet *getPacket() override;

    void draw() override;

private:
    ServerSocket *socket;
    timeval _annimationTime{};
    float _positionX;
    float _positionY;
    float _direction;
};
