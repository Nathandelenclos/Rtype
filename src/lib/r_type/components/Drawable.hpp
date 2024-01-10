/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Drawable.hpp
*/

#pragma once

#include <iostream>
#include <tuple>
#include <memory>
#include "../networking/shared/USocket.hpp"
#include "IComponent.hpp"
#include <SFML/Graphics.hpp>

class Drawable : public IComponentRType {
    public:
        Drawable();
//        Drawable(sf::Vector2f position, sf::Vector2f size, sf::IntRect rect, std::string attribute);
        [[nodiscard]] char *getAttribute() const override;
        void setAttribute(std::string attribute) override;

        std::tuple<float, float> getPosition() const;
        void setPosition(std::tuple<float, float> position);

        std::tuple<float, float> getSize() const;
        void setSize(std::tuple<float, float> size);

        std::tuple<int, int, int, int> getRect() const;
        void setRect(std::tuple<int, int, int, int> rect);

        std::shared_ptr<Packet> getPacket();

        void storeStringInAttributes(std::string str, DrawablePacket *drawablePacket);

        void setHasChanged(bool hasChanged);
        bool getHasChanged() const;

    int _textureId;
protected:
        std::tuple<float, float> _position;
        std::tuple<float, float> _size;
        std::tuple<int, int, int, int> _rect;
        bool hasChanged = false;
};
