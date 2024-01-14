/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "../Components/IComponent.hpp"
#include "../Components/Music/MusicComponent.hpp"
#include "../Components/Sound/SoundComponent.hpp"
#include <memory>
#include <sys/time.h>
#include <vector>

class IScene
{
  public:

    /**
     * @brief IScene, constructor of IScene
     *
     * @param clientCore
     */
    explicit IScene(ClientCore *clientCore) :
        _clientCore(clientCore)
    {
    }

    /**
     * @brief ~IScene, destructor of IScene
     */
    virtual ~IScene() = default;

    /**
     * @brief addComponent, add a component
     *
     * @param component
     */
    virtual void addComponent(std::shared_ptr<IComponent> component) = 0;

    /**
     * @brief getComponents, get all the components
     *
     * @return std::vector<std::shared_ptr<IComponent>>
     */
    virtual std::vector<std::shared_ptr<IComponent>> getComponents() = 0;

    /**
     * @brief display, display the scene
     *
     * @param window
     */
    virtual void display(sf::RenderWindow &window) = 0;

    /**
     * @brief update, update the scene
     */
    virtual void update() = 0;

    /**
     * @brief handleEvent, handle the event
     *
     * @param event
     * @param window
     */
    virtual void handleEvent(const sf::Event &event, sf::RenderWindow &window) = 0;

    /**
     * @brief receiveData, receive the data
     */
    virtual void receiveData() = 0;

    /**
     * @brief pauseScene, pause the scene
     */
    virtual void pauseScene() = 0;

    /**
     * @brief resumeScene, resume the scene
     */
    virtual void resumeScene() = 0;

    /**
     * @brief stopScene, stop the scene
     */
    virtual void stopScene() = 0;

    bool continueScene = true;

  private:
    std::vector<std::shared_ptr<IComponent>> _components;

  protected:
    ClientCore *_clientCore;
    timeval _pingTime{};
};
