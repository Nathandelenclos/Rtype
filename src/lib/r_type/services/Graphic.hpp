/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Graphic.hpp
*/

#pragma once

#include <vector>
#include "IService.hpp"

class Graphic : public IService {
public:
    Graphic() = default;
    void update(IGame *game, std::vector<IObject*> objects) override;
};
