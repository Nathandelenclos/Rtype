/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Animatable.cpp
*/

#include "Animatable.hpp"

#include <cstring>
#include <utility>

/**
 * @brief Construct a new Animatable:: Animatable object
 */
Animatable::Animatable()
{
    _attribute = new char[64];
    std::memset(_attribute, 0, 64);
}

/**
 * @brief getAttribute, get the attribute
 * @return attribute (char *)
 */
char *Animatable::getAttribute() const
{
    return _attribute;
}

/**
 * @brief setAttribute, set the attribute
 * @param attribute
 */
void Animatable::setAttribute(std::string attribute)
{
    std::memset(_attribute, 0, 64);
    std::memcpy(_attribute, attribute.c_str(), attribute.size());
    std::cout << "attribute: " << _attribute << std::endl;
}

/**
 * @brief setTarget, set the target
 * @param target
 */
void Animatable::setTarget(std::shared_ptr<Drawable> target)
{
    sprite = target;
}

/**
 * @brief getTarget, get the target
 * @return target (std::shared_ptr<Drawable>)
 */
std::shared_ptr<Drawable> Animatable::getTarget()
{
    return sprite;
}

/**
 * @brief setTime, set the time
 * @param frametime
 */
void Animatable::setTime(timeval frametime)
{
    _frametime = frametime;
}

/**
 * @brief getTime, get the time
 * @return timeval
 */
timeval Animatable::getTime()
{
    return _frametime;
}
