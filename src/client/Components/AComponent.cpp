//
// Created by Talleux on 28/12/2023.
//

#include "AComponent.hpp"

/**
 * @brief getType, get the type of the component
 */
ComponentType AComponent::getType() const
{
    return _type;
}

/**
 * @brief addActionTarget, add a target to the action
 * @param component
 */
void AComponent::addActionTarget(std::shared_ptr<IComponent> component)
{
    action_target.push_back(std::move(component));
}

/**
 * @brief addSubComponent, add a sub component
 * @param component
 */
void AComponent::addSubComponent(std::shared_ptr<IComponent> component)
{
    sub_components.push_back(std::move(component));
}

/**
 * @brief setAttribute, set the attribute
 * @param attribute
 */
void AComponent::setAttribute(std::string attribute)
{
    _attribute = attribute;
}

/**
 * @brief getAttribute, get the attribute
 * @return attribute
 */
std::string AComponent::getAttribute()
{
    return _attribute;
}
