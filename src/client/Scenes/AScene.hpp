//
// Created by Talleux on 29/12/2023.
//

#pragma once

#include "IScene.hpp"

class AScene : public IScene {
    public:
        ~AScene() override = default;

        void addComponent(std::shared_ptr<IComponent> component) override;
        void display(sf::RenderWindow& window) override;

        void update() override;

    protected:
        std::vector<std::shared_ptr<IComponent>> _components;

};
