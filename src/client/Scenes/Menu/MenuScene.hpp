/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "Components/Button/ButtonComponent.hpp"
#include "Components/Input/InputComponent.hpp"
#include "Components/Music/MusicComponent.hpp"
#include "Components/Sound/SoundComponent.hpp"
#include "Components/Sprite/SpriteComponent.hpp"
#include "Components/Text/TextComponent.hpp"
#include "Scenes/AScene.hpp"
#include "networking/client/ClientSocket.hpp"
#include <memory>
#include <utility>
#include <vector>

class MenuScene : public AScene
{
  public:

    /**
     * @brief MenuScene, constructor of MenuScene
     *
     * @param clientCore
     * @param socket
     */
    explicit MenuScene(ClientCore *clientCore, std::shared_ptr<ClientSocket> socket);

    /**
     * @brief ~MenuScene, destructor of MenuScene
     */
    ~MenuScene() override = default;

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

  private:
    std::shared_ptr<ClientSocket> _socket;
};
