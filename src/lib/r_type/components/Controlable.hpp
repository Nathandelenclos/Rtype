/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Controlable.hpp
*/

#pragma once

#include <iostream>
#include "../../../../include/IObject.hpp"

class Controlable {
public:
    virtual void control() = 0;
};
