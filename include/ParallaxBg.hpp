/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** ParallaxBg.hpp
*/

#pragma once

#include "ParallaxLayer.hpp"
#include <vector>

class ParallaxBackground
{
  public:
    std::vector<ParallaxLayer> layers;

    void addLayer(const std::string &filename, float speed);
    void update(float deltaTime);
};
