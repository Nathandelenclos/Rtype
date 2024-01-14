/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Drawable.hpp
*/

#pragma once

#include "../networking/shared/USocket.hpp"
#include "IComponent.hpp"
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>

typedef std::tuple<float, float> Position;
typedef std::tuple<float, float> Size;
typedef std::tuple<int, int, int, int> Rect;

class Drawable : public IComponentRType
{
  public:
    Drawable();
    [[nodiscard]] char *getAttribute() const;
    void setAttribute(std::string attribute);

    [[nodiscard]] Position getPosition() const;
    void setPosition(std::tuple<float, float> position);

    [[nodiscard]] Size getSize() const;
    void setSize(std::tuple<float, float> size);
    [[nodiscard]] float getScale() const;
    void setScale(float scale);

    [[nodiscard]] Rect getRect() const;
    void setRect(std::tuple<int, int, int, int> rect);

    std::shared_ptr<Packet> getPacket();

    void setHasChanged(bool hasChanged);
    bool getHasChanged() const;

    void addDrawableCollision(std::shared_ptr<Drawable> drawableCollision);
    [[nodiscard]] std::vector<std::shared_ptr<Drawable>> getDrawablesCollision() const;

    int _textureId;
    bool _toDelete = false;

  protected:
    Position _position;
    Size _size;
    Rect _rect;
    float _scale;
    bool hasChanged = false;
    std::vector<std::shared_ptr<Drawable>> _drawablesCollision;
};