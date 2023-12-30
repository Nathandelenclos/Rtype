//
// Created by talleux on 12/29/23.
//

#include "ButtonComponent.hpp"
#include "../../ClientCore.hpp"

#include <utility>

ButtonComponent::ButtonComponent(ClientCore* core, std::shared_ptr<ClientSocket> socket) : AComponent(core)
{
    _type = ComponentType::BUTTON;
    _texture.loadFromFile("../src/client/assets/button.png");
    _sprite.setTexture(_texture);
    _position = sf::Vector2f(150, 100);
    _sprite.setPosition(_position);
    _size = sf::Vector2f(0.75, 0.75);
    _sprite.setScale(_size);
    _rect = sf::IntRect(0, 0, 701, 301);
    _sprite.setTextureRect(_rect);
    _attribute = "";
    _socket = std::move(socket);
    std::function<void()> default_handle_click = std::bind(&ButtonComponent::defaultCallback, this);
    setCallback(default_handle_click);
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

void ButtonComponent::handleClickInitServer()
{
    std::string ip;
    std::string port;
    for (auto &component : action_target) {
        if (component->getType() == ComponentType::INPUT) {
            if (component->getAttribute() == "address") {
                ip = dynamic_cast<InputComponent *>(component.get())->getText();
            } else if (component->getAttribute() == "port") {
                port = dynamic_cast<InputComponent *>(component.get())->getText();
            }
        } else if (component->getType() == ComponentType::SOUND) {
            dynamic_cast<SoundComponent *>(component.get())->action();
        } else if (component->getType() == ComponentType::MUSIC) {
            dynamic_cast<MusicComponent *>(component.get())->setPaused(!dynamic_cast<MusicComponent *>(component.get())->isPlaying());
        }
    }
    if (ip.empty() || port.empty()) {
        for (auto &component : action_target) {
            if (component->getType() == ComponentType::TEXT) {
                if (component->getAttribute() == "text add serv") {
                    dynamic_cast<TextComponent *>(component.get())->setText("Please fill all fields");
                }
            }
        }
    } else {
        for (auto &component: action_target) {
            if (component->getType() == ComponentType::TEXT) {
                if (component->getAttribute() == "text add serv") {
                    try {
                        std::stoi(port);
                    } catch (std::exception &e) {
                        dynamic_cast<TextComponent *>(component.get())->setText("Port must be a number");
                        return;
                    }
                    if (_clientCore->init_socket(ip, std::stoi(port))) {
                        if (!_socket->isInit())
                            dynamic_cast<TextComponent *>(component.get())->setText("Finding server...");
                    } else
                        dynamic_cast<TextComponent *>(component.get())->setText("Server not found");
                }
            } else if (component->getType() == ComponentType::MUSIC) {
                dynamic_cast<MusicComponent *>(component.get())->setVolume(50);
            }
        }
    }
}

void ButtonComponent::handleClickMainScene()
{
    for (auto &component : action_target) {
        if (component->getType() == ComponentType::SOUND) {
            dynamic_cast<SoundComponent *>(component.get())->action();
        }
    }
    _clientCore->setCurrentScene("menu");
}

void ButtonComponent::defaultCallback()
{

}
