//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

typedef enum {
    TEXT,
    SPRITE,
    BUTTON,
    INPUT,
    VARIABLE
} ComponentType;

class IComponent {
    public:
        virtual ~IComponent() = default;

        [[nodiscard]] virtual ComponentType getType() const = 0;
        virtual void action() = 0;
        virtual void display(sf::RenderWindow& window) = 0;
        virtual void addActionTarget(std::unique_ptr<IComponent> component) = 0;
        virtual void addSubComponent(std::unique_ptr<IComponent> component) = 0;

    protected:
        ComponentType _type;
        std::vector<std::unique_ptr<IComponent>> action_target;
        std::vector<std::unique_ptr<IComponent>> sub_components;
};



