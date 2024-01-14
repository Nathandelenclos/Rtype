//
// Created by talleux on 1/10/24.
//

#include "TimeManagement.hpp"
#include "Timer.hpp"

/**
 * @brief update, update the time
 * @param event
 * @param component
 */
void TimeManagement::update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component)
{
    auto time = std::dynamic_pointer_cast<Timer>(component);
    if (time) {
        gettimeofday(&time->_now, nullptr);
        timersub(&time->_now, &time->_startTime, &time->_diff);
        if (time->_diff.tv_sec >= time->_targetTime.tv_sec && time->_diff.tv_usec >= time->_targetTime.tv_usec) {
            if (!time->isActive())
                return;
            auto drawable = time->getTarget();

            if (!drawable)
                return;

            auto position = drawable->getPosition();
            if (std::string(drawable->getAttribute()).find("bullet") != std::string::npos)
                drawable->setPosition(std::make_tuple(std::get<0>(position) + 55, std::get<1>(position)));
            else
                drawable->setPosition(std::make_tuple(std::get<0>(position) + 5 * time->getDirection(), std::get<1>(position)));
            time->_startTime = time->_now;
        }
    }
}
