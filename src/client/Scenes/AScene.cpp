//
// Created by Talleux on 29/12/2023.
//

#include "AScene.hpp"

void AScene::addComponent(std::shared_ptr<IComponent> component) {
    _components.push_back(component);
}

std::vector<std::shared_ptr<IComponent>> AScene::getComponents()
{
    return _components;
}

void AScene::display(sf::RenderWindow &window) {
    for (auto &component: _components) {
        component->display(window);
    }
}

void AScene::update() {
}

void AScene::handleEvent(const sf::Event &event, sf::RenderWindow &window) {
    for (auto &component: _components) {
        component->handleEvent(event, window);
    }
}

void AScene::pauseScene()
{
    for (auto &component : _components) {
        if (component->getType() == MUSIC) {
            auto music = std::dynamic_pointer_cast<MusicComponent>(component);
            if (music->getPersistant())
                continue;
            music->setPaused(false);
        }
    }
}

void AScene::resumeScene()
{
    for (auto &component : _components) {
        if (component->getType() == MUSIC) {
            auto music = std::dynamic_pointer_cast<MusicComponent>(component);
            if (music->getPersistant())
                continue;
            music->setPaused(true);
        }
    }
}

void AScene::stopScene()
{
    for (auto &component : _components) {
        if (component->getType() == MUSIC) {
            auto music = std::dynamic_pointer_cast<MusicComponent>(component);
            music->stop();
        }
    }
}
