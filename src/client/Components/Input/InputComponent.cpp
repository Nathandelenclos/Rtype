//
// Created by talleux on 12/29/23.
//

#include "InputComponent.hpp"
#include <iostream>
#include <utility>

/**
 * @brief InputComponent constructor
 * @param core
 * @param socket
 */
InputComponent::InputComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket) :
    AComponent(core)
{
    _type = ComponentType::INPUT;
    _texture.loadFromFile("../src/client/assets/button.png");
    _sprite.setTexture(_texture);
    _position = sf::Vector2f(100, 400);
    _sprite.setPosition(_position);
    _size = sf::Vector2f(0.75, 0.25);
    _sprite.setScale(_size);
    _rect = sf::IntRect(0, 0, 701, 301);
    _sprite.setTextureRect(_rect);
    _textEntry = "";
    _text.setString(_textEntry);
    _font.loadFromFile("../src/client/assets/fonts/DecemberShow.ttf");
    _text.setFont(_font);
    _position = sf::Vector2f(130, 420);
    _text.setPosition(_position);
    _text.setFillColor(sf::Color::Black);
    _text.setCharacterSize(30);
    _isClicked = false;
    _attribute = "";
    _socket = std::move(socket);
}

/**
 * @brief action, call the callback function
 */
void InputComponent::action()
{
    _callback();
}

/**
 * @brief setTexture set the texture of the component
 * @param texture
 */
void InputComponent::setTexture(const sf::Texture &texture)
{
    _texture = texture;
    _sprite.setTexture(_texture);
}

/**
 * @brief setPosition set the position of the component
 * @param position
 */
void InputComponent::setPosition(sf::Vector2f position)
{
    _position = position;
    _sprite.setPosition(_position);
    sf::Vector2f textPosition = _position;
    textPosition.x += 30;
    textPosition.y += 20;
    _text.setPosition(textPosition);
}

/**
 * @brief setSize set the size of the component
 * @param size
 */
void InputComponent::setSize(sf::Vector2f size)
{
    _size = size;
    _sprite.setScale(_size);
}

/**
 * @brief setRect set the rect of the component
 * @param rect
 */
void InputComponent::setRect(sf::IntRect rect)
{
    _rect = rect;
    _sprite.setTextureRect(_rect);
}

/**
 * @brief display display the component
 * @param window
 */
void InputComponent::display(sf::RenderWindow &window)
{
    window.draw(_sprite);
    window.draw(_text);
}

/**
 * @brief getRect get the texture of the component
 * @return rect of the component
 */
sf::IntRect InputComponent::getRect() const
{
    return _rect;
}

/**
 * @brief setText set the text of the component
 */
void InputComponent::setText()
{
    _text.setString(_textEntry);
}

/**
 * @brief getText get the text of the component
 */
std::string InputComponent::getText()
{
    return _textEntry;
}

/**
 * @brief SetIsClicked set the isClicked of the component
 * @param isClicked
 */
void InputComponent::setIsClicked(bool isClicked)
{
    _isClicked = isClicked;
}

/**
 * @brief handleEvent handle the event of the component
 * @param event
 * @param window
 */
void InputComponent::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::TextEntered) {
        if (_isClicked) {
            if (event.text.unicode < 128) {
                if (event.text.unicode == 8) {
                    if (!_textEntry.empty()) {
                        _textEntry.erase(_textEntry.size() - 1);
                        setText();
                    }
                } else {
                    _textEntry += static_cast<char>(event.text.unicode);
                    setText();
                }
            }
        }
    } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            if (_sprite.getGlobalBounds().contains(mousePosF)) {
                _isClicked = true;
                for (auto &component : action_target) {
                    if (component->getType() == ComponentType::INPUT) {
                        auto input = std::dynamic_pointer_cast<InputComponent>(component);
                        input->setIsClicked(false);
                    }
                }
            } else {
                _isClicked = false;
            }
        }
    }
}
