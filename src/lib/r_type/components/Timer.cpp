//
// Created by talleux on 1/10/24.
//

#include <cstring>
#include <iostream>
#include <utility>
#include "Timer.hpp"

Timer::Timer() {
    _startTime = {0, 0};
    _now = {0, 0};
    _targetTime = {0, 0};
    _diff = {0, 0};
    _attribute = new char[64];
    _active = true;
    std::memset(_attribute, 0, 64);
}

char *Timer::getAttribute() const
{
    return _attribute;
}

void Timer::setAttribute(std::string attribute)
{
    std::memset(_attribute, 0, 64);
    std::memcpy(_attribute, attribute.c_str(), attribute.size());
    std::cout << "attribute: " << _attribute << std::endl;
}

void Timer::setTarget(std::shared_ptr<Drawable> target)
{
    _target = std::move(target);
}

std::shared_ptr<Drawable> Timer::getTarget()
{
    return _target;
}

void Timer::setActive(bool active)
{
    _active = active;
}

bool Timer::isActive() const
{
    return _active;
}
