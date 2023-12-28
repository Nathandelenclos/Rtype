//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include "IComponent.hpp"


class AComponent : public IComponent {
    public:
        ~AComponent() override = default;

        [[nodiscard]] ComponentType getType() const override;
        void action() override = 0;
        void display() override = 0;
        void addActionTarget(std::unique_ptr<IComponent> component) override;
        void addSubComponent(std::unique_ptr<IComponent> component) override;
};
