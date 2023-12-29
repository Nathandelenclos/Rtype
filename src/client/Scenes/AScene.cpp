//
// Created by Talleux on 29/12/2023.
//

#include "AScene.hpp"

void AScene::addComponent(std::shared_ptr<IComponent> component)
{
    _components.push_back(component);
}

void AScene::display(sf::RenderWindow& window)
{
    for (auto &component : _components) {
        component->display(window);
    }
}

void AScene::update()
{
}
