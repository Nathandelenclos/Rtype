/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "../components/IComponent.hpp"
#include <memory>
#include <vector>

class IEntity
{
  public:

    /**
     * @brief Construct a new IEntity object
     *
     */
    IEntity()
    {
        setAttribute("");
    }

    /**
     * @brief Destroy the IEntity object
     *
     */
    ~IEntity() = default;


    /**
     * @brief Get the Components object
     *
     * @return std::vector<std::shared_ptr<IComponentRType>>
     */
    [[nodiscard]] std::vector<std::shared_ptr<IComponentRType>> getComponents() const
    {
        return _components;
    }


    /**
     * @brief addComponent, add a component to the entity
     *
     * @param component
     */
    void addComponent(const std::shared_ptr<IComponentRType> &component)
    {
        _components.push_back(component);
    }

    /**
     * @brief Get the Attribute object
     *
     * @return std::string
     */
    [[nodiscard]] std::string getAttribute() const
    {
        return _attribute;
    }

    /**
     * @brief Set the Attribute object
     *
     * @param attribute
     */
    void setAttribute(const std::string &attribute)
    {
        _attribute = attribute;
    }

  protected:
    std::vector<std::shared_ptr<IComponentRType>> _components;
    std::string _attribute;
};
