//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include "Components/AComponent.hpp"
#include <memory>
#include <string>
#include <vector>

class TextComponent : public AComponent
{
  public:
    explicit TextComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket);

    void display(sf::RenderWindow &window) override;
    void action() override;

    void setText(std::string text);
    void setFont(const sf::Font &font);
    void setPosition(sf::Vector2f position);
    void setColor(sf::Color color);
    void setSize(unsigned int size);

    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

  private:
    std::string _text;
    sf::Font _font;
    sf::Text _sfText;
    sf::Vector2f _position;
    sf::Color _color;
    unsigned int _size{};

    std::vector<std::unique_ptr<IComponent>> _subComponents;
    std::vector<std::unique_ptr<IComponent>> _actionTargets;
    std::shared_ptr<ClientSocket> _socket;
};
