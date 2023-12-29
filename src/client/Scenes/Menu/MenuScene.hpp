//
// Created by Talleux on 29/12/2023.
//

#pragma once

#include <memory>
#include <utility>
#include <vector>
#include "../../../../networking/client/ClientSocket.hpp"
#include "../AScene.hpp"
#include "../../Components/Text/TextComponent.hpp"
#include "../../Components/Button/ButtonComponent.hpp"
#include "../../Components/Input/InputComponent.hpp"
#include "../../Components/Sound/SoundComponent.hpp"
#include "../../Components/Music/MusicComponent.hpp"
#include "../../Components/Sprite/SpriteComponent.hpp"

class MenuScene : public AScene {
    public:
        //take socket as parameter
        explicit MenuScene(ClientCore* clientCore, std::shared_ptr<ClientSocket> socket);
        ~MenuScene() override = default;

        void init_scene();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;

        void receiveData() override;

    private:
        std::shared_ptr<ClientSocket> _socket;
};


