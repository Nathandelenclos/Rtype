/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "TextComponent.hpp"

#include <utility>

/**
 * @brief Construct a new Text Component:: Text Component object
 *
 * @param core
 * @param socket
 */
TextComponent::TextComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket) :
    AComponent(core)
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
    _attribute = "";
    _socket = std::move(socket);
}

void TextComponent::action()
{
}

/**
 * @brief setText, set the text
 * @param text
 */
void TextComponent::setText(std::string text)
{
    _text = std::move(text);
    _sfText.setString(_text);
}

/**
 * @brief setFont, set the font
 * @param font
 */
void TextComponent::setFont(const sf::Font &font)
{
    _font = font;
    _sfText.setFont(_font);
}

/**
 * @brief setPosition, set the position
 * @param position
 */
void TextComponent::setPosition(sf::Vector2f position)
{
    _position = position;
    _sfText.setPosition(_position);
}

/**
 * @brief setColor, set the color
 * @param color
 */
void TextComponent::setColor(sf::Color color)
{
    _color = color;
    _sfText.setFillColor(_color);
}

/**
 * @brief setSize, set the size
 * @param size
 */
void TextComponent::setSize(unsigned int size)
{
    _size = size;
    _sfText.setCharacterSize(_size);
}

/**
 * @brief display, display the text
 * @param window
 */
void TextComponent::display(sf::RenderWindow &window)
{
    window.draw(_sfText);
}

void TextComponent::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
}
