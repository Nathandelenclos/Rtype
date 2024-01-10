/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Controlable.cpp
*/

#include "Animatable.hpp"

#include <utility>
#include <cstring>

Animatable::Animatable()
{
    _attribute = new char[64];
    std::memset(_attribute, 0, 64);
}

char *Animatable::getAttribute() const
{
    return _attribute;
}

void Animatable::setAttribute(std::string attribute)
{
    std::memset(_attribute, 0, 64);
    std::memcpy(_attribute, attribute.c_str(), attribute.size());
    std::cout << "attribute: " << _attribute << std::endl;
}

void Animatable::setTarget(std::shared_ptr<Drawable> target) {
    sprite = target;
}

std::shared_ptr<Drawable> Animatable::getTarget() {
    return sprite;
}

void Animatable::setTime(timeval frametime) {
    _frametime = frametime;
}

timeval Animatable::getTime() {
    return _frametime;
}
