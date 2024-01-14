/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "Components/AComponent.hpp"
#include <memory>
#include <string>
#include <vector>

class TextComponent : public AComponent
{
  public:

    /**
     * @brief Construct a new Text Component:: Text Component object
     *
     * @param core
     * @param socket
     */
    explicit TextComponent(ClientCore *core, std::shared_ptr<ClientSocket> socket);


    /**
     * @brief display the text
     *
     * @param window
     */
    void display(sf::RenderWindow &window) override;

    /**
     * @brief action
     */
    void action() override;

    /**
     * @brief setText, set the text
     *
     * @param text
     */
    void setText(std::string text);

    /**
     * @brief setFont, set the font
     *
     * @param font
     */
    void setFont(const sf::Font &font);

    /**
     * @brief setPosition, set the position
     *
     * @param position
     */
    void setPosition(sf::Vector2f position);

    /**
     * @brief setColor, set the color
     *
     * @param color
     */
    void setColor(sf::Color color);

    /**
     * @brief setSize, set the size
     *
     * @param size
     */
    void setSize(unsigned int size);

    /**
     * @brief handleEvent
     *
     * @param event
     * @param window
     */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

  private:
    std::string _text;
    sf::Font _font;
    sf::Text _sfText;
    sf::Vector2f _position;
    sf::Color _color;
    unsigned int _size{};

    std::vector<std::unique_ptr<IComponent>> _subComponents;
    std::vector<std::unique_ptr<IComponent>> _actionTargets;
    std::shared_ptr<ClientSocket> _socket;
};
