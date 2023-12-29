//
// Created by Talleux on 29/12/2023.
//

#include "MenuScene.hpp"

MenuScene::MenuScene()
{
    init_scene();
}

void MenuScene::init_scene()
{
    std::shared_ptr<TextComponent> text = std::make_shared<TextComponent>();
    std::shared_ptr<ButtonComponent> button = std::make_shared<ButtonComponent>();
    std::shared_ptr<TextComponent> text_button = std::make_shared<TextComponent>();
    std::shared_ptr<InputComponent> address_input = std::make_shared<InputComponent>();
    std::shared_ptr<InputComponent> port_input = std::make_shared<InputComponent>();

    button->addActionTarget(text);
    std::function<void()> handleClick = std::bind(&ButtonComponent::handleClick, button);
    button->setCallback(handleClick);

    text_button->setText("Init Server Connection");
    text_button->setPosition(sf::Vector2f(275, 190));

    address_input->setPosition(sf::Vector2f(150, 380));
    port_input->setPosition(sf::Vector2f(150, 475));

    address_input->addActionTarget(port_input);
    port_input->addActionTarget(address_input);

    addComponent(text);
    addComponent(button);
    addComponent(text_button);
    addComponent(address_input);
    addComponent(port_input);
}

void MenuScene::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    for (auto &component : _components) {
        component->handleEvent(event, window);
    }
}
