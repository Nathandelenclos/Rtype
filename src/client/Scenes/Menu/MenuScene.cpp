//
// Created by Talleux on 29/12/2023.
//

#include "MenuScene.hpp"

#include <utility>

MenuScene::MenuScene(std::shared_ptr<ClientSocket> socket) : _socket(std::move(socket)) {
    init_scene();
}

void MenuScene::init_scene()
{
    std::shared_ptr<TextComponent> text = std::make_shared<TextComponent>(_socket);
    std::shared_ptr<ButtonComponent> button = std::make_shared<ButtonComponent>(_socket);
    std::shared_ptr<TextComponent> text_button = std::make_shared<TextComponent>(_socket);
    std::shared_ptr<InputComponent> address_input = std::make_shared<InputComponent>(_socket);
    std::shared_ptr<InputComponent> port_input = std::make_shared<InputComponent>(_socket);
    std::shared_ptr<SoundComponent> sound = std::make_shared<SoundComponent>(_socket);
    std::shared_ptr<MusicComponent> music = std::make_shared<MusicComponent>(_socket);
    std::shared_ptr<SpriteComponent> sprite = std::make_shared<SpriteComponent>(_socket);

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

    addComponent(sprite);
    addComponent(text);
    addComponent(button);
    addComponent(text_button);
    addComponent(address_input);
    addComponent(port_input);
    addComponent(sound);
    addComponent(music);
}

void MenuScene::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
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
    }

}
