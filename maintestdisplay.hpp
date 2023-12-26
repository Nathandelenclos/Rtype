/*
** EPITECH PROJECT, 2023
** RType
** File description:
** maintestdisplay.hpp
*/

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "lib/DLLoader.hpp"

class Sprite {
    public:
        Sprite(std::string path, int animationLimit = 0);
        ~Sprite() = default;
        void animateSprite(int frameCount, int frameToBegin, int numberFrameToAnim, float switchTime, int top, int bottom, sf::Clock clock, sf::RenderWindow& window);
        void drawSprite(sf::RenderWindow& window) { window.draw(_Sprite); };
        int getSizeY() { return _Texture.getSize().y; };
        int getSizeX() { return _Texture.getSize().x; };

    protected:
        sf::Texture _Texture;
        sf::Sprite _Sprite;
        int _AnimationLimit;
        int _NumberAnimation;
        bool _EndAnimation;

};
