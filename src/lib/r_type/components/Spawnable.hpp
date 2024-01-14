/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Spawnable.hpp
*/

#pragma once

#include <iostream>
#include <tuple>
#include <memory>
#include <sys/time.h>
#include "../networking/shared/USocket.hpp"
#include "IComponent.hpp"
#include "Drawable.hpp"


class Spawnable : public IComponentRType {
    public:
        Spawnable();
        [[nodiscard]] char *getAttribute() const override;
        void setAttribute(std::string attribute) override;
        void setTarget(std::shared_ptr<Drawable> target);
        std::shared_ptr<Drawable> getTarget();
        void setTimeBetweenWave(std::tuple<int, int> frametime);
        std::tuple<int, int> getTimeBetweenWave();
        timeval _now;
        timeval _diff;
        timeval _chrono;
        std::tuple<int, int> _speedWave;
        std::tuple<int, int> _numberEntityWave;

    protected:
        std::tuple<int, int> _timeBetweenWave;
        std::shared_ptr<Drawable> sprite;
};
