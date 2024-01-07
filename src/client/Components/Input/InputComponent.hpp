//
// Created by talleux on 12/29/23.
//

#pragma once

#include <functional>
#include "../AComponent.hpp"

class InputComponent : public AComponent {
    public:
        explicit InputComponent(ClientCore* core, std::shared_ptr<ClientSocket> socket);
        void action() override;
        void setTexture(const sf::Texture& texture);
        void setPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setRect(sf::IntRect rect);
        void setIsClicked(bool isClicked);
        void display(sf::RenderWindow& window) override;

        sf::IntRect getRect() const;

        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;
        void handleClick();

        void setText();
        std::string getText();


    std::string _textEntry;
private:
        sf::Texture _texture;
        sf::Text _text;
        sf::Font _font;
        sf::Sprite _sprite;
        sf::Vector2f _position;
        sf::Vector2f _size;
        sf::IntRect _rect;
        std::function<void()> _callback;
    bool _isClicked;
        std::shared_ptr<ClientSocket> _socket;
};
