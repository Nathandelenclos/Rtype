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
    Player() {
        std::cout << "Player constructor" << std::endl;
    }

    void draw() override {
        std::cout << "Player::draw()" << std::endl;
    }
};
