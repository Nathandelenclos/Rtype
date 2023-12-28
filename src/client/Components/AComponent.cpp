//
// Created by Talleux on 28/12/2023.
//

#include "AComponent.hpp"

AComponent::AComponent(ComponentType type)
{
    _type = type;
}

ComponentType AComponent::getType() const
{
    return _type;
}

void AComponent::addActionTarget(std::unique_ptr<IComponent> component)
{
    action_target.push_back(std::move(component));
}

void AComponent::addSubComponent(std::unique_ptr<IComponent> component)
{
    sub_components.push_back(std::move(component));
}
