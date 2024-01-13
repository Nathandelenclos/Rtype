//
// Created by Talleux on 29/12/2023.
//

#include "AScene.hpp"

/**
 * @brief addComponent, add a component to the scene
 * @param component
 */
void AScene::addComponent(std::shared_ptr<IComponent> component)
{
    _components.push_back(component);
}

/**
 * @brief getComponents, get all the components of the scene
 * @return std::vector<std::shared_ptr<IComponent>>
 */
std::vector<std::shared_ptr<IComponent>> AScene::getComponents()
{
    return _components;
}

/**
 * @brief display, display the scene
 * @param window
 */
void AScene::display(sf::RenderWindow &window)
{
    for (auto &component : _components) {
        component->display(window);
    }
}

void AScene::update()
{
}

/**
 * @brief handleEvent, handle the event
 * @param event
 * @param window
 */
void AScene::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    for (auto &component : _components) {
        component->handleEvent(event, window);
    }
}

/**
 * @brief pauseScene, pause the scene
 */
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

/**
 * @brief resumeScene, resume the scene
 */
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

/**
 * @brief stopScene, stop the scene
 */
void AScene::stopScene()
{
    for (auto &component : _components) {
        if (component->getType() == MUSIC) {
            auto music = std::dynamic_pointer_cast<MusicComponent>(component);
            music->stop();
        }
    }
}
