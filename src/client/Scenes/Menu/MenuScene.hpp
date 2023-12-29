//
// Created by Talleux on 29/12/2023.
//

#pragma once

#include <memory>
#include <vector>
#include "../AScene.hpp"
#include "../../Components/Text/TextComponent.hpp"
#include "../../Components/Button/ButtonComponent.hpp"
#include "../../Components/Input/InputComponent.hpp"

class MenuScene : public AScene {
    public:
        MenuScene();
        ~MenuScene() override = default;

        void init_scene();
        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
};


