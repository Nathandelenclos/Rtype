//
// Created by talleux on 1/10/24.
//

#pragma once

#include "AService.hpp"
#include "IComponent.hpp"
#include <utility>
#include <vector>

class TimeManagement : public AService
{
  public:
    explicit TimeManagement(std::shared_ptr<ServerSocket> serverSocket) :
        AService(std::move(serverSocket)){};

    void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;
};
