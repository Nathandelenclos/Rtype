/*
** EPITECH PROJECT, 2023
** RType
** File description:
** maintestdisplay.cpp
*/

#include "maintestdisplay.hpp"

Sprite::Sprite(std::string path, int animationLimit) {
    if (!_Texture.loadFromFile(path)) {
        // Gestion de l'erreur si le chargement de la texture échoue
    } else {
        _Sprite.setTexture(_Texture);
        _AnimationLimit = animationLimit;
        _NumberAnimation = 0;
        _EndAnimation = false;
    }
}

void Sprite::animateSprite(int frameCount, int frameToBegin, int numberFrameToAnim, float switchTime, int top, int bottom, sf::Clock clock, sf::RenderWindow& window) {
    if (_AnimationLimit != 0 && _NumberAnimation >= _AnimationLimit)
        return;
    // Calculer la largeur de chaque frame
    int frameWidth = _Texture.getSize().x / frameCount;

    // Calculer le temps écoulé depuis le début de l'animation
    float time = clock.getElapsedTime().asSeconds();

    frameCount = numberFrameToAnim;

    // Calculer l'indice de la frame actuelle
    int frameIndex = static_cast<int>(int((time / switchTime)) % frameCount);

    // Définir la région de texture à afficher
    sf::IntRect textureRect(frameWidth * (frameToBegin - 1 + frameIndex), top, frameWidth, bottom);

    _Sprite.setTextureRect(textureRect);
    if (frameIndex == frameCount - 1) {
        if (_EndAnimation == false)
            _NumberAnimation++;
        _EndAnimation = true;
    } else {
        _EndAnimation = false;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Clock clock;
    Sprite explosion("sprites/r-typesheet44.gif");

    DLLoader loader("../test_lib_r_type.so");

    IGame *game = loader.getInstance("create");

    game->run();

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        explosion.animateSprite(10, 6, 5, 0.3, 98, explosion.getSizeY(), clock, window);
        explosion.drawSprite(window);
        window.display();
    }

    return 0;
}
