/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** ParallaxBg.cpp
*/

#include "ParallaxBg.hpp"

void ParallaxBackground::addLayer(const std::string &filename, float speed)
{
    ParallaxLayer layer;
    layer.loadTexture(filename);
    layer._speed = speed;
    layers.push_back(layer);
}

void ParallaxBackground::update(float deltaTime)
{
    for (auto &layer : layers) {
        layer.update(deltaTime);
    }
}