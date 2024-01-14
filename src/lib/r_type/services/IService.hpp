//
// Created by talleux on 1/4/24.
//

#pragma once

#include "../components/IComponent.hpp"
#include "../networking/server/ServerSocket.hpp"

class IService
{
  public:
    virtual ~IService() = default;
    virtual void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) = 0;

  protected:
    std::shared_ptr<ServerSocket> _serverSocket;
};
