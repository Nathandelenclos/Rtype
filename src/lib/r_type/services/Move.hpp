/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "AService.hpp"
#include "Drawable.hpp"

class Move : public AService
{
  public:

    /**
     * @brief Construct a new Move:: Move object
     * @param serverSocket
     */
    explicit Move(std::shared_ptr<ServerSocket> serverSocket) :
        AService(std::move(serverSocket)){};

    /**
     * @brief update, update the move
     *
     * @param event
     * @param component
     */
    void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;
};
