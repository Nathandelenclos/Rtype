/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Spawner.cpp
*/

#include "Spawnable.hpp"
#include "Spawner.hpp"

void Spawner::update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component)
{
    auto animatable = std::dynamic_pointer_cast<Animatable>(component);
    if (animatable) {
        gettimeofday(&animatable->_now, NULL);
        timersub(&animatable->_now, &animatable->_chrono, &animatable->_diff);
        if (animatable->_diff.tv_sec >= animatable->getTime().tv_sec && animatable->_diff.tv_usec >= animatable->getTime().tv_usec) {
            auto spriteAnim = animatable->getTarget();
            int numberFrameToAnim = animatable->_numberFrameToAnim - 1;
            std::tuple<float, float> size = spriteAnim->getSize();
            if (animatable->_frameIndex >= numberFrameToAnim + animatable->_startFrameIndex) {
                animatable->_frameIndex = animatable->_startFrameIndex;
            } else {
                animatable->_frameIndex++;
            }
            int frameWidth1 = std::get<0>(size) / spriteAnim->getScale() / animatable->_numberFrame * animatable->_frameIndex;
            int frameWidth2 = std::get<0>(size) / spriteAnim->getScale() / animatable->_numberFrame * animatable->_frameForOnePicture;
            int frameHeight = std::get<1>(size) / spriteAnim->getScale();
            spriteAnim->setRect(std::make_tuple(frameWidth1, 0, frameWidth2, frameHeight));
            animatable->_chrono = animatable->_now;
        }
    }
}
