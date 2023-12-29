//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include "../Components/IComponent.hpp"

class IScene {
    public:
        virtual ~IScene() = default;

        virtual void addComponent(std::shared_ptr<IComponent> component) = 0;
        virtual void display(sf::RenderWindow& window) = 0;

        virtual void update() = 0;
        virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;

    private:
        std::vector<std::shared_ptr<IComponent>> _components;
};
