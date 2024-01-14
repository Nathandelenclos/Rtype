/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** GameScene.cpp
*/

#pragma once

#include "../AScene.hpp"
#include "Components/Sprite/SpriteComponent.hpp"
#include "networking/shared/USocket.hpp"
#include <iostream>

class GameScene : public AScene
{
  public:

    /**
     * @brief GameScene, constructor of GameScene
     *
     * @param clientCore
     * @param socket
     */
    GameScene(ClientCore *clientCore, std::shared_ptr<ClientSocket> socket);

    /**
     * @brief ~GameScene, destructor of GameScene
     */
    ~GameScene() override = default;


    /**
     * @brief init_scene, init the scene
     */
    void init_scene();

    /**
     * @brief handleEvent, handle the event
     *
     * @param event
     * @param window
     */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

    /**
     * @brief receiveData, receive the data
     */
    void receiveData() override;

    /**
     * @brief getTextureByType, get the texture by type
     *
     * @param type
     */
    sf::Texture getTextureByType(Type type) const;

    /**
     * @brief initTextures, init the textures
     */
    void initTextures();

  private:
    std::shared_ptr<ClientSocket> _socket;
    std::map<Type, sf::Texture> _textures;
};
