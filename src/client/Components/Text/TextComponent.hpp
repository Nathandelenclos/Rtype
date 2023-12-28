//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "../AComponent.hpp"

class TextComponent : public AComponent {
    public:
        TextComponent();
        ~TextComponent() override = default;

        void display(sf::RenderWindow& window);

        void setText(std::string text);
        void setFont(const sf::Font& font);
        void setPosition(sf::Vector2f position);
        void setColor(sf::Color color);
        void setSize(unsigned int size);

    private:
        std::string _text;
        sf::Font _font;
        sf::Text _sfText;
        sf::Vector2f _position;
        sf::Color _color;
        unsigned int _size{};

        std::vector<std::unique_ptr<IComponent>> _subComponents;
        std::vector<std::unique_ptr<IComponent>> _actionTargets;

};
