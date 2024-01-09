/*
** EPITECH PROJECT, 2023
** rtype
** File description:
** ParallaxBg.cpp
*/

#include "ParallaxLayer.hpp"

void ParallaxLayer::loadTexture(const std::string& filename)
{
    _texture.loadFromFile(filename);
    _sprite.setTexture(_texture);
}

void ParallaxLayer::update(float deltaTime)
{
    float movement = _speed * deltaTime;
    _sprite.move(-movement, 0);

    if (_sprite.getPosition().x + _sprite.getLocalBounds().width < 0) {
        _sprite.setPosition(_sprite.getLocalBounds().width * 4, 0);
    }
}
