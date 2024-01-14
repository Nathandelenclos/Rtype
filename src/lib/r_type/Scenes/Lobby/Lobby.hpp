/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "../AScene.hpp"
#include "../components/Animatable.hpp"
#include "../components/Drawable.hpp"
#include "../components/Timer.hpp"
#include <SFML/Window/Keyboard.hpp>

class LobbyScene : public AScene
{
  public:

    /**
     * @brief Construct a new LobbyScene object
     * @param serverSocket
     */
    explicit LobbyScene(std::shared_ptr<ServerSocket> serverSocket);

    /**
     * @brief Destroy the LobbyScene object
     */
    ~LobbyScene() override = default;


    /**
     * @brief initScene, init the scene
     */
    void initScene();


    /**
     * @brief display, display the scene
     *
     * @param event
     * @param window
     */
    void update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet) override;


    /**
     * @brief checkBulletDeletion, check if a bullet has to be deleted
     */
    void checkBulletDeletion();

    /**
     * @brief display, display the scene
     */
    void initEntities() override;
    void initServices() override;

  private:
    timeval _chrono;
    std::shared_ptr<Event> _lastEvent;
    timeval _bulletTriggerLimiter;
    int _nbBullets;
};
