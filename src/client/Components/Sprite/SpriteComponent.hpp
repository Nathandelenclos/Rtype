/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "Components/AComponent.hpp"
#include <SFML/Graphics.hpp>

class SpriteComponent : public AComponent
{
  public:

    /**
     * @brief Construct a new Sprite Component:: Sprite Component object
     *
     * @param core
     * @param socket
     */
    explicit SpriteComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket);

    /**
     * @brief Destroy the Sprite Component:: Sprite Component object
     *
     */
    ~SpriteComponent() override = default;

    /**
     * @brief action
     *
     */
    void action() override;

    /**
     * @brief setTexture, set the texture
     *
     * @param texture
     */
    void setTexture(const sf::Texture &texture);

    /**
     * @brief setPosition, set the position
     *
     * @param position
     */
    void setPosition(sf::Vector2f position);

    /**
     * @brief setPosition, set the position
     *
     * @param x
     * @param y
     */
    void setPosition(float x, float y);

    /**
     * @brief setSize, set the size
     *
     * @param size
     */
    void setSize(sf::Vector2f size);

    /**
     * @brief setRect, set the rect
     *
     * @param rect
     */
    void setRect(sf::IntRect rect);

    /**
     * @brief display, display the sprite
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

  private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::IntRect _rect;
    std::shared_ptr<ClientSocket> _socket;
};
