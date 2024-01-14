/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "Components/AComponent.hpp"
#include "Components/Input/InputComponent.hpp"
#include "Components/Music/MusicComponent.hpp"
#include "Components/Sound/SoundComponent.hpp"
#include "Components/Text/TextComponent.hpp"
#include <functional>
#include <iostream>

class ButtonComponent : public AComponent
{
  public:

    /**
     * @brief Construct a new Button Component object
     *
     * @param core
     * @param socket
     */
    explicit ButtonComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket);

    /**
     * @brief Destroy the Button Component object
     *
     */
    void action() override;

    /**
     * @brief Set the Texture object
     *
     * @param texture
     */
    void setTexture(const sf::Texture &texture);

    /**
     * @brief Set the Position object
     *
     * @param position
     */
    void setPosition(sf::Vector2f position);

    /**
     * @brief Set the Size object
     *
     * @param size
     */
    void setSize(sf::Vector2f size);

    /**
     * @brief Set the Callback object
     *
     * @param callback
     */
    void setCallback(std::function<void()> callback);

    /**
     * @brief Set the Rect object
     *
     * @param rect
     */
    void setRect(sf::IntRect rect);

    /**
     * @brief display the button
     * @param window
     */
    void display(sf::RenderWindow &window) override;

    /**
     * @brief Get the Rect object
     *
     * @return sf::IntRect
     */
    sf::IntRect getRect() const;

    /**
     * @brief handle event, check if the button is clicked
     * @param event
     * @param window
     */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

    /**
     * @brief handleClickInitServer,  handle click on init server button
     */
    void handleClickInitServer();

    /**
     * @brief handleClickMainScene, handle click on main scene button
     */
    void handleClickMainScene();

    /**
     * @brief handleClickMenuScene, handle click on menu scene button
     */
    void handleClickAccessGame();

    /**
     * @brief defaultCallback, default callback
     */
    void defaultCallback();

  private:
    sf::Texture _texture;
    sf::Sprite _sprite;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::IntRect _rect;
    std::function<void()> _callback;
    std::shared_ptr<ClientSocket> _socket;
};
