//
// Created by Talleux on 29/12/2023.
//

#include "MenuScene.hpp"
#include "../../ClientCore.hpp"

#include <utility>

MenuScene::MenuScene(ClientCore* clientCore, std::shared_ptr<ClientSocket> socket) : AScene(clientCore), _socket(std::move(socket))
{
    init_scene();
    _pingTime.tv_sec = 0;
    _pingTime.tv_usec = 0;
}

void MenuScene::init_scene()
{
    std::shared_ptr<TextComponent> text = std::make_shared<TextComponent>(_clientCore, _socket);
    std::shared_ptr<ButtonComponent> button = std::make_shared<ButtonComponent>(_clientCore, _socket);
    std::shared_ptr<TextComponent> text_button = std::make_shared<TextComponent>(_clientCore, _socket);
    std::shared_ptr<InputComponent> address_input = std::make_shared<InputComponent>(_clientCore, _socket);
    std::shared_ptr<InputComponent> port_input = std::make_shared<InputComponent>(_clientCore, _socket);
    std::shared_ptr<SoundComponent> sound = std::make_shared<SoundComponent>(_clientCore, _socket);
    std::shared_ptr<MusicComponent> music = std::make_shared<MusicComponent>(_clientCore, _socket);
    std::shared_ptr<SpriteComponent> sprite = std::make_shared<SpriteComponent>(_clientCore, _socket);
    std::shared_ptr<TextComponent> text_ping = std::make_shared<TextComponent>(_clientCore, _socket);

    button->addActionTarget(text);
    button->addActionTarget(address_input);
    button->addActionTarget(port_input);
    button->addActionTarget(sound);
    button->addActionTarget(music);
    std::function<void()> handleClick = std::bind(&ButtonComponent::handleClickInitServer, button);
    button->setCallback(handleClick);

    text_button->setText("Init Server Connection");
    text_button->setPosition(sf::Vector2f(275, 190));

    address_input->setPosition(sf::Vector2f(150, 380));
    port_input->setPosition(sf::Vector2f(150, 475));

    address_input->addActionTarget(port_input);
    port_input->addActionTarget(address_input);

    address_input->setAttribute("address");
    port_input->setAttribute("port");
    text->setAttribute("text add serv");

    text_ping->setAttribute("text ping");
    text_ping->setText("Ping: 0ms");
    text_ping->setPosition(sf::Vector2f(0, 550));

    addComponent(sprite);
    addComponent(text);
    addComponent(button);
    addComponent(text_button);
    addComponent(address_input);
    addComponent(port_input);
    addComponent(sound);
    addComponent(music);
    addComponent(text_ping);
}

void MenuScene::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            _clientCore->setCurrentScene("main");
            return;
        }
    }
    for (auto &component : _components) {
        component->handleEvent(event, window);
    }
}

void MenuScene::receiveData() {
    std::tuple<std::unique_ptr<Packet>, int> packet = _socket->receive();
    std::unique_ptr<Packet> p = std::move(std::get<0>(packet));

    if (p != nullptr) {
        if (p->code == MESSAGE) {
            std::string message = static_cast<char *>(p->data);
            if (message == "connection accepted") {
                for (auto &component : _components) {
                    if (component->getType() == ComponentType::TEXT) {
                        if (component->getAttribute() == "text add serv") {
                            dynamic_cast<TextComponent *>(component.get())->setText("Connection accepted");
                        }
                    }
                }
            }
        }
        if (p->code == HEARTBEAT) {
            timeval timerecv{};
            timeval now{};
            gettimeofday(&now, nullptr);
            timerecv = *static_cast<timeval *>(p->data);
            timersub(&now, &timerecv, &_pingTime);

            for (auto &component : _components) {
                if (component->getType() == ComponentType::TEXT) {
                    if (component->getAttribute() == "text ping") {
                        dynamic_cast<TextComponent *>(component.get())->setText("Ping: " + std::to_string(_pingTime.tv_sec * 1000 + _pingTime.tv_usec / 1000) + ", " + std::to_string(_pingTime.tv_usec % 1000) + "ms");
                    }
                }
            }
        }
    }

}
