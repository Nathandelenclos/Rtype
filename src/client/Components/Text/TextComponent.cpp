//
// Created by Talleux on 28/12/2023.
//

#include "TextComponent.hpp"

#include <utility>

TextComponent::TextComponent()
{
    _type = ComponentType::TEXT;
    _text = "base_text";
    _sfText.setString(_text);
    _font.loadFromFile("../src/client/assets/fonts/DecemberShow.ttf");
    _sfText.setFont(_font);
    _position = sf::Vector2f(0, 0);
    _sfText.setPosition(_position);
    _color = sf::Color::White;
    _sfText.setFillColor(_color);
    _size = 30;
    _sfText.setCharacterSize(_size);
}

void TextComponent::action()
{
}

void TextComponent::setText(std::string text)
{
    _text = std::move(text);
    _sfText.setString(_text);
}

void TextComponent::setFont(const sf::Font& font)
{
    _font = font;
    _sfText.setFont(_font);
}

void TextComponent::setPosition(sf::Vector2f position)
{
    _position = position;
    _sfText.setPosition(_position);
}

void TextComponent::setColor(sf::Color color)
{
    _color = color;
    _sfText.setFillColor(_color);
}

void TextComponent::setSize(unsigned int size)
{
    _size = size;
    _sfText.setCharacterSize(_size);
}

void TextComponent::display(sf::RenderWindow& window)
{
    window.draw(_sfText);
}
