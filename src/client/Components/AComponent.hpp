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
        void addActionTarget(std::shared_ptr<IComponent> component) override;
        void addSubComponent(std::shared_ptr<IComponent> component) override;

        void setAttribute(std::string attribute) override;
        std::string getAttribute() override;
};
