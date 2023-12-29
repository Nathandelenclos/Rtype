//
// Created by Talleux on 28/12/2023.
//

#include "AComponent.hpp"

ComponentType AComponent::getType() const
{
    return _type;
}

void AComponent::addActionTarget(std::shared_ptr<IComponent> component)
{
    action_target.push_back(std::move(component));
}

void AComponent::addSubComponent(std::shared_ptr<IComponent> component)
{
    sub_components.push_back(std::move(component));
}

void AComponent::setAttribute(std::string attribute)
{
    _attribute = attribute;
}

std::string AComponent::getAttribute()
{
    return _attribute;
}
