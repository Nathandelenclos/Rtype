//
// Created by Talleux on 29/12/2023.
//

#pragma once

#include <memory>
#include <vector>
#include "../AScene.hpp"
#include "../../Components/Text/TextComponent.hpp"

class MenuScene : public AScene {
    public:
        MenuScene();
        ~MenuScene() override = default;

        void init_scene();

};


