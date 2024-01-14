/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "AService.hpp"
#include "IComponent.hpp"
#include <utility>
#include <vector>

class TimeManagement : public AService
{
  public:

/**
     * @brief Construct a new TimeManagement:: TimeManagement object
     * @param serverSocket
     */
    explicit TimeManagement(std::shared_ptr<ServerSocket> serverSocket) :
        AService(std::move(serverSocket)){};

    /**
     * @brief update, update the time management
     *
     * @param event
     * @param component
     */
    void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;
};
