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
#include <vector>
#include "../networking/shared/USocket.hpp"
#include "IComponent.hpp"

typedef std::tuple<float, float> Position;
typedef std::tuple<float, float> Size;
typedef std::tuple<int, int, int, int> Rect;

class Drawable : public IComponentRType {
    public:
        Drawable();
        [[nodiscard]] char *getAttribute() const override;
        void setAttribute(std::string attribute) override;

        [[nodiscard]] Position getPosition() const;
        void setPosition(std::tuple<float, float> position);

        [[nodiscard]] Size getSize() const;
        void setSize(std::tuple<float, float> size);

        [[nodiscard]] Rect getRect() const;
        void setRect(std::tuple<int, int, int, int> rect);

        std::shared_ptr<Packet> getPacket();

        void storeStringInAttributes(std::string str, DrawablePacket *drawablePacket);

        void setHasChanged(bool hasChanged);
        bool getHasChanged() const;

        void addDrawableCollision(std::shared_ptr<Drawable> drawableCollision);
        std::vector<std::shared_ptr<Drawable>> getDrawablesCollision() const;

    int _textureId;
protected:
        Position _position;
        Size _size;
        Rect _rect;
        bool hasChanged = false;
        std::vector<std::shared_ptr<Drawable>> _drawablesCollision;
};
