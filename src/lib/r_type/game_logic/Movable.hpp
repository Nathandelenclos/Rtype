/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Movable.hpp
*/

#pragma once

#include <iostream>
#include "../../../../include/IObject.hpp"

class Movable {
public:
    virtual void move() = 0;
    virtual void getSpeed(int speed) = 0;
};