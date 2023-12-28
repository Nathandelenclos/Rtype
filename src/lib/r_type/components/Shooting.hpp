/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Shooting.hpp
*/

#pragma once

#include <iostream>
#include "../../../../include/IObject.hpp"

class Shooting {
public:
    virtual void shoot() = 0;
    virtual void getShootType() = 0;
    virtual void getShootDirection() = 0;
    virtual void getShootDamage() = 0;
};
