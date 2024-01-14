/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "../../networking/server/ServerSocket.hpp"
#include "../components/IComponent.hpp"
#include "../entities/IEntity.hpp"
#include "../services/Animation.hpp"
#include "../services/Graphic.hpp"
#include "../services/IService.hpp"
#include "../services/TimeManagement.hpp"
#include <memory>
#include <vector>

class ISceneRType
{
  public:

    /**
     * @brief Construct a new IScene:: IScene object
     * @param serverSocket
     */
    virtual ~ISceneRType() = default;

    /**
     * @brief display, display the scene
     */
    virtual void display() = 0;

    /**
     * @brief update, update the scene
     * @param event
     * @param packet
     */
    virtual void update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet) = 0;

    /**
     * @brief pauseScene, pause the scene
     */
    virtual void pauseScene() = 0;

    /**
     * @brief resumeScene, resume the scene
     */
    virtual void resumeScene() = 0;

    /**
     * @brief stopScene, stop the scene
     */
    virtual void stopScene() = 0;

    /**
     * @brief restartScene, restart the scene
     */
    virtual void restartScene() = 0;


    /**
     * @brief addEntity, add an entity
     * @param entity
     */
    virtual void addEntity(std::shared_ptr<IEntity> entity) = 0;

    /**
     * @brief getEntities, get the entities
     * @return entities (std::vector<std::shared_ptr<IEntity>>)
     */
    virtual std::vector<std::shared_ptr<IEntity>> getEntities() = 0;


    /**
     * @brief addService, add a service
     * @param service
     */
    virtual void addService(std::shared_ptr<IService> service) = 0;

    /**
     * @brief getServices, get the services
     * @return services (std::vector<std::shared_ptr<IService>>)
     */
    virtual std::vector<std::shared_ptr<IService>> getServices() = 0;


    /**
     * @brief sendGameState, send the game state to a client
     * @param clientId
     */
    virtual void sendGameState(int clientId) = 0;

    /**
     * @brief broadcastGameState, broadcast the game state
     */
    virtual void broadcastGameState() = 0;


    /**
     * @brief initEntities, init the entities
     */
    virtual void initEntities() = 0;

    /**
     * @brief initServices, init the services
     */
    virtual void initServices() = 0;

  protected:
    std::vector<std::shared_ptr<IEntity>> _entities;
    std::vector<std::shared_ptr<IService>> _services;
    std::shared_ptr<ServerSocket> _serverSocket;
};
