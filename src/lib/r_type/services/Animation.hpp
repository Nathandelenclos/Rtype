/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Animation.hpp
*/

#pragma once

#include <utility>
#include <vector>
#include "AService.hpp"
#include "IComponent.hpp"

class Animation : public AService {
public:
    explicit Animation(std::shared_ptr<ServerSocket> serverSocket) : AService(std::move(serverSocket)) {};

    void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;
};