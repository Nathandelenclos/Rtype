//
// Created by Talleux on 29/12/2023.
//

#pragma once

#include "IScene.hpp"

class AScene : public IScene {
    public:
        explicit AScene(ClientCore* clientCore) : IScene(clientCore) {}
        ~AScene() override = default;

        void addComponent(std::shared_ptr<IComponent> component) override;
        void display(sf::RenderWindow& window) override;
        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void update() override;

        void pauseScene() override;
        void resumeScene() override;
        void stopScene() override;

    protected:
        std::vector<std::shared_ptr<IComponent>> _components;
};
