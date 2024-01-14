/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Graphic.hpp
*/

#pragma once

#include "AService.hpp"
#include "IComponent.hpp"
#include <utility>
#include <vector>

class Graphic : public AService
{
  public:

    /**
     * @brief Construct a new Graphic:: Graphic object
     * @param serverSocket
     */
    explicit Graphic(std::shared_ptr<ServerSocket> serverSocket) :
        AService(std::move(serverSocket)){};

    /**
     * @brief update, update the graphic
     * @param event
     * @param component
     */
    void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;
};
