//
// Created by Talleux on 29/12/2023.
//

#pragma once

#include "../AScene.hpp"

class MenuScene : public AScene {
    public:
        MenuScene();
        ~MenuScene() override = default;

        void display() override;

};


