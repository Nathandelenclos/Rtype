/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Spawner.hpp
*/

#pragma once

#include <utility>
#include <vector>
#include "AService.hpp"
#include "IComponent.hpp"

class Spawner : public AService {
public:
    explicit Spawner(std::shared_ptr<ServerSocket> serverSocket) : AService(std::move(serverSocket)) {};

    void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;
};