//
// Created by talleux on 12/29/23.
//

#include "ButtonComponent.hpp"

ButtonComponent::ButtonComponent()
{
    _type = ComponentType::BUTTON;
    _texture.loadFromFile("../src/client/assets/button.png");
    _sprite.setTexture(_texture);
    _position = sf::Vector2f(150, 150);
    _sprite.setPosition(_position);
    _size = sf::Vector2f(1, 1);
    _sprite.setScale(_size);
    _rect = sf::IntRect(0, 0, 350, 301);
    _sprite.setTextureRect(_rect);
}

void ButtonComponent::action()
{
    _callback();
}

void ButtonComponent::setTexture(const sf::Texture& texture)
{
    _texture = texture;
    _sprite.setTexture(_texture);
}

void ButtonComponent::setPosition(sf::Vector2f position)
{
    _position = position;
    _sprite.setPosition(_position);
}

void ButtonComponent::setSize(sf::Vector2f size)
{
    _size = size;
    _sprite.setScale(_size);
}

void ButtonComponent::setRect(sf::IntRect rect)
{
    _rect = rect;
    _sprite.setTextureRect(_rect);
}

void ButtonComponent::setCallback(std::function<void()> callback)
{
    _callback = std::move(callback);
}

void ButtonComponent::display(sf::RenderWindow& window)
{
    window.draw(_sprite);
}

sf::IntRect ButtonComponent::getRect() const
{
    return _rect;
}

void ButtonComponent::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            if (_sprite.getGlobalBounds().contains(mousePosF)) {
                action();
            }
        }
    }
}

void ButtonComponent::handleClick()
{
    for (auto &component : action_target) {
        if (component->getType() == ComponentType::TEXT) {
            std::shared_ptr<TextComponent> text = std::dynamic_pointer_cast<TextComponent>(component);
            text->setText("Button clicked");
        }
    }
}
