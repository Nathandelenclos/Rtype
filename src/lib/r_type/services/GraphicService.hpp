/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Graphic.hpp
*/

#pragma once

#include <vector>
#include "IService.hpp"

class GraphicService : public IService {
public:
    GraphicService() = default;
    void update(std::vector<IObject*> objects) override;
};
