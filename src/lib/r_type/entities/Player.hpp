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
    Player() = default;
    ~Player() = default;
    Packet *getPacket() const override;

    void draw() override;
};
