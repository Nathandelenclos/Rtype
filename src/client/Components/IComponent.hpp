//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "../../../networking/client/ClientSocket.hpp"

typedef enum {
    TEXT,
    SPRITE,
    BUTTON,
    INPUT,
    VARIABLE,
    MUSIC,
    SOUND
} ComponentType;

class ClientCore;

class IComponent {
    public:
        explicit IComponent(ClientCore* clientCore) : _clientCore(clientCore) {}
        virtual ~IComponent() = default;

        [[nodiscard]] virtual ComponentType getType() const = 0;
        virtual void action() = 0;
        virtual void display(sf::RenderWindow& window) = 0;
        virtual void addActionTarget(std::shared_ptr<IComponent> component) = 0;
        virtual void addSubComponent(std::shared_ptr<IComponent> component) = 0;

        virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) = 0;

        virtual void setAttribute(std::string attribute) = 0;
        virtual std::string getAttribute() = 0;

    protected:
        std::string _attribute;
        ComponentType _type;
        std::vector<std::shared_ptr<IComponent>> action_target;
        std::vector<std::shared_ptr<IComponent>> sub_components;
        ClientCore* _clientCore;
};



