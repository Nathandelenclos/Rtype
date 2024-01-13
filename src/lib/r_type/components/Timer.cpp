//
// Created by talleux on 1/10/24.
//

#include "Timer.hpp"
#include <cstring>
#include <iostream>
#include <utility>

/**
 * @brief Construct a new Timer:: Timer object
 */
Timer::Timer()
{
    _startTime = {0, 0};
    _now = {0, 0};
    _targetTime = {0, 0};
    _diff = {0, 0};
    _attribute = new char[64];
    _active = true;
    std::memset(_attribute, 0, 64);
}

/**
 * @brief getAttribute, get the attribute
 * @return attribute (char *)
 */
char *Timer::getAttribute() const
{
    return _attribute;
}

/**
 * @brief setAttribute, set the attribute
 * @param attribute
 */
void Timer::setAttribute(std::string attribute)
{
    std::memset(_attribute, 0, 64);
    std::memcpy(_attribute, attribute.c_str(), attribute.size());
    std::cout << "attribute: " << _attribute << std::endl;
}

/**
 * @brief setTarget, set the target
 * @param target
 */
void Timer::setTarget(std::shared_ptr<Drawable> target)
{
    _target = std::move(target);
}

/**
 * @brief setTarget, set the target
 * @return target
 */
std::shared_ptr<Drawable> Timer::getTarget()
{
    return _target;
}

/**
 * @brief setActive, set the timer active
 * @param active
 */
void Timer::setActive(bool active)
{
    _active = active;
}

/**
 * @brief isActive, check if the timer is active
 * @return active (bool)
 */
bool Timer::isActive() const
{
    return _active;
}
