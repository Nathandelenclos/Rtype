/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** ParallaxBg.hpp
*/

#pragma once

#include "maintestdisplay.hpp"

class ParallaxLayer
{
  public:
    void loadTexture(const std::string &filename);
    void update(float deltaTime);

    float _speed;
    sf::Sprite _sprite;
    sf::Texture _texture;

  protected:
};
