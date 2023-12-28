//
// Created by Talleux on 29/12/2023.
//

#include "AScene.hpp"

void AScene::addComponent(std::unique_ptr<IComponent> component)
{
    _components.push_back(std::move(component));
}

void AScene::display()
{
    for (auto &component : _components) {
        component->display();
    }
}
