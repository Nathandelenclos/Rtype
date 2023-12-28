/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Collidable.hpp
*/

#pragma once

#include <iostream>
#include "../../../../include/IObject.hpp"

class Collidable {
public:
    virtual void collision() = 0;
};
