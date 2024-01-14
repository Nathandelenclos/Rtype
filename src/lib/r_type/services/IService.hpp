//
// Created by talleux on 1/4/24.
//

#pragma once

#include "../components/IComponent.hpp"
#include "../networking/server/ServerSocket.hpp"

class IService
{
  public:

    /**
     * @brief Construct a new IService:: IService object
     * @param serverSocket
     */
    virtual ~IService() = default;

    /**
     * @brief update, update the service
     * @param event
     * @param component
     */
    virtual void update(std::shared_ptr<Event> event, std::shared_ptr<IComponentRType> component) = 0;

  protected:
    std::shared_ptr<ServerSocket> _serverSocket;
};
