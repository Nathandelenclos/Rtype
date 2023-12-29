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
        //std::cout << "RType constructor" << std::endl;
        objects.push_back(new Player());
        services.push_back(new Graphic());
    }

    ~RType() override {
        //std::cout << "RType destructor" << std::endl;
    }

    [[nodiscard]] std::vector<IObject*> getObjects() const override {
        //std::cout << "RType::getObjects()" << std::endl;
        return objects;
    }

    [[nodiscard]] std::vector<IService*> getServices() const override {
        //std::cout << "RType::getServices()" << std::endl;
        return services;
    }

    std::vector<IObject*> objects;
    std::vector<IService*> services;
};
