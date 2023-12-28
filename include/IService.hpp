/*
** EPITECH PROJECT, 2023
** RType
** File description:
** IObject.hpp
*/

#pragma once

#include <vector>
#include "IObject.hpp"

class IService {
public:
    virtual void update(std::vector<IObject*> objects) = 0;
};
