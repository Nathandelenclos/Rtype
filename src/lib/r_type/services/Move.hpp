//
// Created by nathan on 1/10/24.
//

#pragma once

#include "AService.hpp"
#include "Drawable.hpp"

class Move : public AService
{
  public:
    explicit Move(std::shared_ptr<ServerSocket> serverSocket) :
        AService(std::move(serverSocket)){};
    void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) override;
};
