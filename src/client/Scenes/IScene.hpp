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

    private:
        std::vector<std::unique_ptr<IComponent>> _components;
};
