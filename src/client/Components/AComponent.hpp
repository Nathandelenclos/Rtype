/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "IComponent.hpp"
#include <memory>
#include <vector>

class AComponent : public IComponent
{
  public:

    /**
     * @brief AComponent, constructor of AComponent
     */
    explicit AComponent(ClientCore *clientCore) :
        IComponent(clientCore)
    {
    }

    /**
     * @brief ~AComponent, destructor of AComponent
     */
    ~AComponent() override = default;

    /**
     * @brief getType, get the type of the component
     */
    [[nodiscard]] ComponentType getType() const override;

    /**
     * @brief addActionTarget, add a target to the action
     * @param component
     */
    void addActionTarget(std::shared_ptr<IComponent> component) override;

    /**
     * @brief addSubComponent, add a sub component
     * @param component
     */
    void addSubComponent(std::shared_ptr<IComponent> component) override;

    /**
     * @brief setAttribute, set the attribute
     * @param attribute
     */
    void setAttribute(std::string attribute) override;

    /**
     * @brief getAttribute, get the attribute
     * @return attribute
     */
    [[nodiscard]]
    std::string getAttribute() override;
};
