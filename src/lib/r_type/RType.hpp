/*
** EPITECH PROJECT, 2023
** RType
** File description:
** RType.hpp
*/

#pragma once

#include <iostream>
#include "../../../include/IGame.hpp"
#include "./entities/Player.hpp"
#include "./services/Graphic.hpp"

class RType : public IGame {
public:
    RType() {
        objects.push_back(new Player());
        services.push_back(new Graphic());
    }

    ~RType() override {
        for (auto &object : objects)
            delete object;
        for (auto &service : services)
            delete service;
    }

    [[nodiscard]] std::vector<IObject*> getObjects() const override {
        return objects;
    }

    [[nodiscard]] std::vector<IService*> getServices() const override {
        return services;
    }

    std::vector<IObject*> objects;
    std::vector<IService*> services;
};
