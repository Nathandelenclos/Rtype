/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Animatable.hpp
*/

#pragma once

#include "../networking/shared/USocket.hpp"
#include "Drawable.hpp"
#include "IComponent.hpp"
#include <iostream>
#include <memory>
#include <sys/time.h>
#include <tuple>

class Animatable : public IComponentRType
{
  public:
    Animatable();
    [[nodiscard]] char *getAttribute() const override;
    void setAttribute(std::string attribute) override;
    void setTarget(std::shared_ptr<Drawable> target);
    std::shared_ptr<Drawable> getTarget();
    void setTime(timeval frametime);
    timeval getTime();
    timeval _now;
    timeval _diff;
    timeval _chrono;
    int _numberFrameToAnim;
    int _frameIndex;
    int _numberFrame;
    int _startFrameIndex;
    int _frameForOnePicture;

  protected:
    std::shared_ptr<Drawable> sprite;
    timeval _frametime;
};

// class Sprite {
//     public:
//         Sprite(std::string path, int animationLimit = 0);
//         ~Sprite() = default;
//         void animateSprite(int frameCount, int frameToBegin, int numberFrameToAnim, float switchTime, int top, int
//         bottom, sf::Clock clock, sf::RenderWindow& window); void drawSprite(sf::RenderWindow& window) {
//         window.draw(_Sprite); }; int getSizeY() { return _Texture.getSize().y; }; int getSizeX() { return
//         _Texture.getSize().x; };

//     protected:
//         sf::Texture _Texture;
//         sf::Sprite _Sprite;
//         int _AnimationLimit;
//         int _NumberAnimation;
//         bool _EndAnimation;

// };
