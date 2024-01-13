//
// Created by talleux on 12/29/23.
//

#pragma once

#include "Components/AComponent.hpp"
#include <SFML/Graphics.hpp>

class SpriteComponent : public AComponent
{
  public:
    explicit SpriteComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket);
    ~SpriteComponent() override = default;

    void action() override;
    void setTexture(const sf::Texture &texture);
    void setPosition(sf::Vector2f position);
    void setPosition(float x, float y);
    void setSize(sf::Vector2f size);
    void setRect(sf::IntRect rect);
    void display(sf::RenderWindow &window) override;

    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

  private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::IntRect _rect;
    std::shared_ptr<ClientSocket> _socket;
};
