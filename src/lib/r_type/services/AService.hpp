/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "IComponent.hpp"
#include "IService.hpp"

class AService : public IService
{
  public:

    /**
     * @brief Construct a new AService:: AService object
     * @param serverSocket
     */
    explicit AService(std::shared_ptr<ServerSocket> serverSocket);

    /**
     * @brief Destroy the AService:: AService object
     */
    ~AService() override = default;

    virtual void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) = 0;
};
