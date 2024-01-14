/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "../AComponent.hpp"
#include <functional>

class InputComponent : public AComponent
{
  public:

    /**
     * @brief Construct a new Input Component object
     *
     * @param core
     * @param socket
     */
    explicit InputComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket);

    /**
     * @brief action, call the callback function
     *
     */
    void action() override;

    /**
     * @brief setTexture set the texture of the component
     *
     * @param texture
     */
    void setTexture(const sf::Texture &texture);

    /**
     * @brief setPosition set the position of the component
     *
     * @param position
     */
    void setPosition(sf::Vector2f position);

    /**
     * @brief setSize set the size of the component
     *
     * @param size
     */
    void setSize(sf::Vector2f size);

    /**
     * @brief setRect set the rect of the component
     *
     * @param rect
     */
    void setRect(sf::IntRect rect);

    /**
     * @brief setIsClicked, set the isClicked of the component
     */
    void setIsClicked(bool isClicked);

    /**
     * @brief display display the component
     *
     * @param window
     */
    void display(sf::RenderWindow &window) override;

    /**
     * @brief getRect get the rect of the component
     *
     * @return sf::IntRect
     */
    sf::IntRect getRect() const;

    /**
     * @brief handleEvent, handle the event
     *
     * @param event
     * @param window
     */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

    /**
     * @brief handleClick, handle the click
     *
     */
    void handleClick();

    /**
     * @brief setText, set the text of the component
     *
     */
    void setText();

    /**
     * @brief getText, get the text of the component
     *
     */
    std::string getText();

    std::string _textEntry;

  private:
    sf::Texture _texture;
    sf::Text _text;
    sf::Font _font;
    sf::Sprite _sprite;
    sf::Vector2f _position;
    sf::Vector2f _size;
    sf::IntRect _rect;
    std::function<void()> _callback;
    bool _isClicked;
    std::shared_ptr<ClientSocket> _socket;
};
