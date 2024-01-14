/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Controlable.hpp
*/

#pragma once

#include "../../../../include/IObject.hpp"
#include <iostream>

class Controlable
{
  public:
    virtual void control() = 0;
};
