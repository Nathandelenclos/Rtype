/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "../components/Drawable.hpp"
#include "../components/IComponent.hpp"
#include "IScene.hpp"

class AScene : public ISceneRType
{
  public:

    /**
     * @brief Construct a new AScene:: AScene object
     * @param serverSocket
     */
    explicit AScene(std::shared_ptr<ServerSocket> serverSocket);

    /**
     * @brief Destroy the AScene:: AScene object
     */
    ~AScene() override = default;

    /**
     * @brief addEntity, add an entity
     * @param entity
     */
    void addEntity(std::shared_ptr<IEntity> entity) override;

    /**
     * @brief getEntities, get the entities
     * @return entities (std::vector<std::shared_ptr<IEntity>>)
     */
    std::vector<std::shared_ptr<IEntity>> getEntities() override;

    /**
     * @brief addService, add a service
     * @param service
     */
    void addService(std::shared_ptr<IService> service) override;

    /**
     * @brief getServices, get the services
     * @return services (std::vector<std::shared_ptr<IService>>)
     */
    std::vector<std::shared_ptr<IService>> getServices() override;

    /**
     * @brief display, display the scene
     */
    void display() override;

    /**
     * @brief pauseScene, pause the scene
     */
    void pauseScene() override;

    /**
     * @brief resumeScene, resume the scene
     */
    void resumeScene() override;

    /**
     * @brief stopScene, stop the scene
     */
    void stopScene() override;

    /**
     * @brief restartScene, restart the scene
     */
    void restartScene() override;


    /**
     * @brief sendGameState, send the game state
     */
    void sendGameState(int clientID) override;

    /**
     * @brief broadcastGameState, broadcast the game state
     */
    void broadcastGameState() override;

  protected:
};
