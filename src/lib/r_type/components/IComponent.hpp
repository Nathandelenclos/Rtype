/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once
#include <iostream>

class IComponentRType
{
  public:

    /**
     * @brief Construct a new IComponentRType object
     */
    virtual ~IComponentRType() = default;


    /**
     * @brief getAttribute, get the attribute
     *
     * @return attribute (char *)
     */
    [[nodiscard]] virtual char *getAttribute() const = 0;

    /**
     * @brief setAttribute, set the attribute
     *
     * @param attribute
     */
    virtual void setAttribute(std::string attribute) = 0;

  protected:
    char *_attribute;
};
