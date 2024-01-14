/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "ButtonComponent.hpp"
#include "../../ClientCore.hpp"

#include <utility>

/**
 * @brief ButtonComponent constructor
 * @param core
 * @param socket
 */
ButtonComponent::ButtonComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket) :
    AComponent(core)
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

/**
 * @brief action, call the callback function
 */
void ButtonComponent::action()
{
    _callback();
}

/**
 * @brief setTexture set the texture of the button
 * @param texture
 */
void ButtonComponent::setTexture(const sf::Texture &texture)
{
    _texture = texture;
    _sprite.setTexture(_texture);
}

/**
 * @brief setPosition set the position of the button
 * @param position
 */
void ButtonComponent::setPosition(sf::Vector2f position)
{
    _position = position;
    _sprite.setPosition(_position);
}

/**
 * @brief setSize set the size of the button
 * @param size
 */
void ButtonComponent::setSize(sf::Vector2f size)
{
    _size = size;
    _sprite.setScale(_size);
}

/**
 * @brief setRect set the rect of the button
 * @param rect
 */
void ButtonComponent::setRect(sf::IntRect rect)
{
    _rect = rect;
    _sprite.setTextureRect(_rect);
}

/**
 * @brief setAttribute set the attribute of the button
 * @param attribute
 */
void ButtonComponent::setCallback(std::function<void()> callback)
{
    _callback = std::move(callback);
}

/**
 * @brief setAttribute set the attribute of the button
 * @param window
 */
void ButtonComponent::display(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

/**
 * @brief getRect get the texture of the button
 * @return rect of the button
 */
sf::IntRect ButtonComponent::getRect() const
{
    return _rect;
}

/**
 * @brief handleEvent handle the event of the button
 * @param event to handle
 * @param window
 */
void ButtonComponent::handleEvent(const sf::Event &event, sf::RenderWindow &window)
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

/**
 * @brief handleClickInitServer handle the click of the button
 */
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
        for (auto &component : action_target) {
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
            }
        }
    }
}

/**
 * @brief handleClickMainScene handle the click of the button on the main scene
 */
void ButtonComponent::handleClickMainScene()
{
    for (auto &component : action_target) {
        if (component->getType() == ComponentType::SOUND) {
            dynamic_cast<SoundComponent *>(component.get())->action();
        }
        if (component->getType() == ComponentType::MUSIC) {
            auto music = dynamic_cast<MusicComponent *>(component.get());
            if (music->getPersistant())
                continue;
            music->stop();
        }
    }
    _clientCore->setCurrentScene("menu");
}

/**
 * @brief handleClickAccessGame handle the click of the button for access the game scene
 */
void ButtonComponent::handleClickAccessGame()
{
    for (auto &component : action_target) {
        if (component->getType() == ComponentType::SOUND) {
            dynamic_cast<SoundComponent *>(component.get())->action();
        }
    }
    if (!_socket->isInit()) {
        for (auto &component : action_target) {
            if (component->getType() == ComponentType::TEXT) {
                if (component->getAttribute() == "text error not init") {
                    dynamic_cast<TextComponent *>(component.get())->setText("Please init server connection");
                }
            }
        }
        return;
    }
    for (auto &component : action_target) {
        if (component->getType() == ComponentType::MUSIC) {
            auto music = dynamic_cast<MusicComponent *>(component.get());
            music->stop();
        }
    }
    _clientCore->setCurrentScene("game");
    Packet packet{};
    packet.code = CODE::MESSAGE;
    packet.data_size = 10;
    packet.data = malloc(packet.data_size);
    memcpy(packet.data, "enter game", packet.data_size);
    _socket->send(&packet, _socket->serv_addr);
    free(packet.data);
}

void ButtonComponent::defaultCallback()
{
}
