//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include "networking/client/ClientSocket.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

/**
 * @brief ComponentType, enum of the component type
 */
typedef enum {
    TEXT,
    SPRITE,
    BUTTON,
    INPUT,
    VARIABLE,
    MUSIC,
    SOUND,
} ComponentType;

class ClientCore;

class IComponent
{
  public:

    /**
     * @brief IComponent, constructor of IComponent
     */
    explicit IComponent(ClientCore *clientCore) :
        _clientCore(clientCore)
    {
    }

    /**
     * @brief ~IComponent, destructor of IComponent
     */
    virtual ~IComponent() = default;


    /**
     * @brief getType, get the type of the component
     */
    [[nodiscard]] virtual ComponentType getType() const = 0;

    /**
     * @brief action, action of the component
     */
    virtual void action() = 0;

    /**
     * @brief display, display the component
     * @param window
     */
    virtual void display(sf::RenderWindow &window) = 0;

    /**
     * @brief addActionTarget, add a target to the action
     * @param component
     */
    virtual void addActionTarget(std::shared_ptr<IComponent> component) = 0;

    /**
     * @brief addSubComponent, add a sub component
     * @param component
     */
    virtual void addSubComponent(std::shared_ptr<IComponent> component) = 0;


    /**
     * @brief handleEvent, handle the event
     * @param event
     * @param window
     */
    virtual void handleEvent(const sf::Event &event, sf::RenderWindow &window) = 0;


    /**
     * @brief setAttribute, set the attribute
     * @param attribute
     */
    virtual void setAttribute(std::string attribute) = 0;

    /**
     * @brief getAttribute, get the attribute
     * @return attribute
     */
    [[nodiscard]]
    virtual std::string getAttribute() = 0;

  protected:
    std::string _attribute;
    ComponentType _type;
    std::vector<std::shared_ptr<IComponent>> action_target;
    std::vector<std::shared_ptr<IComponent>> sub_components;
    ClientCore *_clientCore;
};
