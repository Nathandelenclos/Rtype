//

#include "SpriteComponent.hpp"

SpriteComponent::SpriteComponent(ClientCore* core, std::shared_ptr<ClientSocket> socket) : AComponent(core)
{
    _socket = std::move(socket);
    if (!_texture.loadFromFile("../src/client/assets/missing.png"))
        throw std::runtime_error("Cannot load sprite texture");
    _rect = sf::IntRect(0, 0, static_cast<int>(_texture.getSize().x), static_cast<int>(_texture.getSize().y));
    _position = sf::Vector2f(0, 0);
    _sprite.setTexture(_texture);
    _sprite.setPosition(_position);
    setSize(sf::Vector2f(200, 200));
    _sprite.setTextureRect(_rect);
    _type = ComponentType::SPRITE;
}

void SpriteComponent::action()
{
}

void SpriteComponent::display(sf::RenderWindow& window)
{
    window.draw(_sprite);
}

void SpriteComponent::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
}

void SpriteComponent::setTexture(const sf::Texture& texture)
{
    _texture = texture;
    _sprite.setTexture(_texture);
}

void SpriteComponent::setPosition(sf::Vector2f position)
{
    _position = position;
    _sprite.setPosition(_position);
}

void SpriteComponent::setSize(sf::Vector2f size)
{
    _size = size;
    _sprite.setScale(_size.x / _texture.getSize().x, _size.y / _texture.getSize().y);
}

void SpriteComponent::setRect(sf::IntRect rect)
{
    _rect = rect;
    _sprite.setTextureRect(_rect);
}

void SpriteComponent::setPosition(float x, float y)
{
    _position = sf::Vector2f(x, y);
    _sprite.setPosition(_position);
}
