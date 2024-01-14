/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Animation.hpp
*/

#pragma once

#include "AService.hpp"
#include "IComponent.hpp"
#include <utility>
#include <vector>

class Animation : public AService
{
  public:

    /**
     * @brief Construct a new Animation:: Animation object
     * @param serverSocket
     */
    explicit Animation(std::shared_ptr<ServerSocket> serverSocket) :
        AService(std::move(serverSocket)){};

    /**
     * @brief Destroy the Animation:: Animation object
     *
     * @param event
     * @param component
     */
    void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;
};
