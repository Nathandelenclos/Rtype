//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include "IComponent.hpp"


class AComponent : public IComponent {
    public:
        AComponent(ComponentType type);
        virtual ~AComponent() = default;

        [[nodiscard]] virtual ComponentType getType() const;
        virtual void action() = 0;
        virtual void addActionTarget(std::unique_ptr<IComponent> component);
        virtual void addSubComponent(std::unique_ptr<IComponent> component);
};
