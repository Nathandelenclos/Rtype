/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Controlable.cpp
*/

#include "Animation.hpp"
#include "Animatable.hpp"

void Animation::update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component)
{
    auto animatable = std::dynamic_pointer_cast<Animatable>(component);
    if (animatable) {
        gettimeofday(&animatable->_now, NULL);
        timersub(&animatable->_now, &animatable->_chrono, &animatable->_diff);
        if (animatable->_diff.tv_sec >= animatable->getTime().tv_sec &&
            animatable->_diff.tv_usec >= animatable->getTime().tv_usec) {
            auto spriteAnim = animatable->getTarget();
            int numberFrameToAnim = animatable->_numberFrameToAnim - 1;
            std::tuple<float, float> size = spriteAnim->getSize();
            if (animatable->_frameIndex >= numberFrameToAnim + animatable->_startFrameIndex) {
                animatable->_frameIndex = animatable->_startFrameIndex;
            } else {
                animatable->_frameIndex++;
            }
            int frameWidth1 =
                std::get<0>(size) / spriteAnim->getScale() / animatable->_numberFrame * animatable->_frameIndex;
            int frameWidth2 =
                std::get<0>(size) / spriteAnim->getScale() / animatable->_numberFrame * animatable->_frameForOnePicture;
            int frameHeight = std::get<1>(size) / spriteAnim->getScale();

            // std::cout << "frameWidth1: " << frameWidth1 << std::endl;
            // std::cout << "frameWidth2: " << frameWidth2 << std::endl;
            // std::cout << "frameHeight: " << frameHeight << std::endl;

            // spriteAnim->setRect(std::make_tuple((std::get<0>(size) / spriteAnim->getScale() /
            // animatable->_numberFrame * animatable->_frameIndex), 0, (std::get<0>(size) / spriteAnim->getScale() /
            // animatable->_numberFrame * (animatable->_frameIndex + 1)), std::get<1>(size)));
            spriteAnim->setRect(std::make_tuple(frameWidth1, 0, frameWidth2, frameHeight));
            animatable->_chrono = animatable->_now;
        }
    }
}

// Animation::Animation(std::string path, int animationLimit) {
//     if (!_Texture.loadFromFile(path)) {
//         // Gestion de l'erreur si le chargement de la texture échoue
//     } else {
//         _Sprite.setTexture(_Texture);
//         _AnimationLimit = animationLimit;
//         _NumberAnimation = 0;
//         _EndAnimation = false;
//     }
// }

// void Animation::Animation(int frameCount, int frameToBegin, int numberFrameToAnim, float switchTime, int top, int
// bottom, sf::Clock clock, sf::RenderWindow& window) {
//     if (_AnimationLimit != 0 && _NumberAnimation >= _AnimationLimit)
//         return;
//     // Calculer la largeur de chaque frame
//     int frameWidth = _Texture.getSize().x / frameCount;

//     // Calculer le temps écoulé depuis le début de l'animation
//     float time = clock.getElapsedTime().asSeconds();

//     frameCount = numberFrameToAnim;

//     // Calculer l'indice de la frame actuelle
//     int frameIndex = static_cast<int>(int((time / switchTime)) % frameCount);

//     // Définir la région de texture à afficher
//     sf::IntRect textureRect(frameWidth * (frameToBegin - 1 + frameIndex), top, frameWidth, bottom);

//     _Sprite.setTextureRect(textureRect);
//     if (frameIndex == frameCount - 1) {
//         if (_EndAnimation == false)
//             _NumberAnimation++;
//         _EndAnimation = true;
//     } else {
//         _EndAnimation = false;
//     }
// }

// explosion.animateSprite(10, 6, 5, 0.3, 98, explosion.getSizeY(), clock, window);
