//
// Created by talleux on 1/10/24.
//

#pragma once

#include "../networking/shared/USocket.hpp"
#include "Drawable.hpp"
#include "IComponent.hpp"

class Timer : public IComponentRType
{
  public:

    /**
     * @brief Construct a new Timer:: Timer object
     */
    Timer();


    /**
     * @brief getAttribute, get the attribute
     *
     * @return attribute (char *)
     */
    [[nodiscard]] char *getAttribute() const override;

    /**
     * @brief setAttribute, set the attribute
     *
     * @param attribute
     */
    void setAttribute(std::string attribute) override;

    /**
     * @brief setTarget, set the target
     *
     * @param target
     */
    void setTarget(std::shared_ptr<Drawable> target);

    /**
     * @brief getTarget, get the target
     *
     * @return target (std::shared_ptr<Drawable>)
     */
    std::shared_ptr<Drawable> getTarget();


    /**
     * @brief setActive, set the timer active
     *
     * @param active
     */
        void setActive(bool active);

    /**
     * @brief getActive, get the timer active
     *
     * @return active (bool)
     */
    bool isActive() const;

    void setDirection(int direction);
    int getDirection() const;


    timeval _startTime{};
    timeval _now{};
    timeval _targetTime{};
    timeval _diff{};

    protected:
        std::shared_ptr<Drawable> _target;
        bool _active;
        int _direction;



};
