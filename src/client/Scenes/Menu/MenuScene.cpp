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
    button->addActionTarget(text);
    std::function<void()> handleClick = std::bind(&ButtonComponent::handleClick, button);
    button->setCallback(handleClick);
    addComponent(text);
    addComponent(button);
}

void MenuScene::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    for (auto &component : _components) {
        component->handleEvent(event, window);
    }
}
