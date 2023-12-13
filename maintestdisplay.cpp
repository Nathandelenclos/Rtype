//
// Created by talleux on 12/13/23.
//

#include "maintestdisplay.hpp"

Sprite::Sprite(std::string path) {
    if (!_Texture.loadFromFile(path)) {
        // Gestion de l'erreur si le chargement de la texture échoue
    } else {
        _Sprite.setTexture(_Texture);
    }
}

void Sprite::animateSprite(int frameCount, int animationStop, float switchTime, int top, int bottom, sf::Clock clock, sf::RenderWindow& window) {
    // Calculer la largeur de chaque frame
    int frameWidth = _Texture.getSize().x / frameCount;

    // Calculer le temps écoulé depuis le début de l'animation
    float time = clock.getElapsedTime().asSeconds();

    frameCount = animationStop;

    // Calculer l'indice de la frame actuelle
    int frameIndex = static_cast<int>(int((time / switchTime)) % frameCount);

    // Définir la région de texture à afficher
    sf::IntRect textureRect(frameIndex * frameWidth, top, frameWidth, bottom);
    
    _Sprite.setTextureRect(textureRect);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::Clock clock;
    Sprite explosion("sprites/r-typesheet44.gif");

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        explosion.animateSprite(10, 10, 0.1, 98, explosion.getSizeY(), clock, window);
        explosion.drawSprite(window);
        window.display();
    }

    return 0;
}
