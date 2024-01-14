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
    Timer();

    [[nodiscard]] char *getAttribute() const override;
    void setAttribute(std::string attribute) override;

        void setTarget(std::shared_ptr<Drawable> target);
        std::shared_ptr<Drawable> getTarget();

        void setActive(bool active);
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
