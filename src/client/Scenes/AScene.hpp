/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "IScene.hpp"

class AScene : public IScene
{
  public:

    /**
     * @brief AScene, constructor of AScene
     *
     * @param clientCore
     */
    explicit AScene(ClientCore *clientCore) :
        IScene(clientCore)
    {
    }

    /**
     * @brief ~AScene, destructor of AScene
     */
    ~AScene() override = default;


    /**
     * @brief addComponent, add a component
     *
     * @param component
     */
    void addComponent(std::shared_ptr<IComponent> component) override;

    /**
     * @brief getComponents, get all the components
     *
     * @return std::vector<std::shared_ptr<IComponent>>
     */
    std::vector<std::shared_ptr<IComponent>> getComponents() override;

    /**
     * @brief display, display the scene
     *
     * @param window
     */
    void display(sf::RenderWindow &window) override;

    /**
     * @brief handleEvent, handle the event
     *
     * @param event
     * @param window
     */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

    /**
     * @brief update, update the scene
     */
    void update() override;

    /**
     * @brief pauseScene, pause the scene
     */
    void pauseScene() override;

    /**
     * @brief resumeScene, resume the scene
     */
    void resumeScene() override;

    /**
     * @brief stopScene, stop the scene
     */
    void stopScene() override;

  protected:
    std::vector<std::shared_ptr<IComponent>> _components;
};
