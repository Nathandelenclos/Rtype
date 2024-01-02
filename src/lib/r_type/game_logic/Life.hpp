/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Life.hpp
*/

#pragma once

#include <iostream>
#include "../../../../include/IObject.hpp"

class Life {
public:
    virtual void changeLife() = 0;
    virtual void getLife() = 0;
};
