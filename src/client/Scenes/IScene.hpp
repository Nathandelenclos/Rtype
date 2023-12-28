//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include "../Components/IComponent.hpp"

class IScene {
    public:
        virtual ~IScene() = default;

        virtual void addComponent(std::unique_ptr<IComponent> component) = 0;
        virtual void display() = 0;

    private:
        std::vector<std::unique_ptr<IComponent>> _components;
};
