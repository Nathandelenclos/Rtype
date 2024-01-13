//
// Created by talleux on 12/29/23.
//

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
#include <vector>

class MainScene : public AScene
{
  public:
    // take socket as parameter
    explicit MainScene(ClientCore *clientCore, std::shared_ptr<ClientSocket> socket);
    ~MainScene() override = default;

    void init_scene();
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

    void receiveData() override;

  private:
    std::shared_ptr<ClientSocket> _socket;
};
