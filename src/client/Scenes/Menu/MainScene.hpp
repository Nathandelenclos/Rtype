//
// Created by talleux on 12/29/23.
//

#pragma once

#include <memory>
#include <vector>
#include "../../../../networking/client/ClientSocket.hpp"
#include "../AScene.hpp"
#include "../../Components/Text/TextComponent.hpp"
#include "../../Components/Button/ButtonComponent.hpp"
#include "../../Components/Input/InputComponent.hpp"
#include "../../Components/Sound/SoundComponent.hpp"
#include "../../Components/Music/MusicComponent.hpp"

class MainScene : public AScene {
    public:
        //take socket as parameter
        explicit MainScene(std::shared_ptr<ClientSocket> socket);
        ~MainScene() override = default;

        void init_scene();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;

        void receiveData();

    private:
        std::shared_ptr<ClientSocket> _socket;

};
