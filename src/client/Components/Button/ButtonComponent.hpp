//
// Created by talleux on 12/29/23.
//

#pragma once

#include <functional>
#include <iostream>
#include "../AComponent.hpp"
#include "../Text/TextComponent.hpp"
#include "../Input/InputComponent.hpp"

class ButtonComponent : public AComponent {
    public:
        explicit ButtonComponent(std::shared_ptr<ClientSocket> socket);
        void action() override;
        void setTexture(const sf::Texture& texture);
        void setPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setCallback(std::function<void()> callback);
        void setRect(sf::IntRect rect);
        void display(sf::RenderWindow& window) override;

        sf::IntRect getRect() const;

        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void handleClickInitServer();

    private:
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Vector2f _position;
        sf::Vector2f _size;
        sf::IntRect _rect;
        std::function<void()> _callback;
        std::shared_ptr<ClientSocket> _socket;
};
