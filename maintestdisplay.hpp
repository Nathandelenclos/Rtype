#ifndef MAINTESTDISPLAY_HPP
#define MAINTESTDISPLAY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Sprite {
    public:
        Sprite(std::string path);
        ~Sprite() = default;
        void animateSprite(int frameCount, int animationStop, float switchTime, int top, sf::Clock clock, sf::RenderWindow& window);
        void drawSprite(sf::RenderWindow& window);

    protected:
        sf::Texture _Texture;
        sf::Sprite _Sprite;

};

#endif // MAINTESTDISPLAY_HPP
