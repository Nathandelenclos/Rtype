/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Drawable.cpp
*/

#include "Drawable.hpp"

#include <utility>
#include <cstring>

Drawable::Drawable()
{
    setPosition({0, 0});
    setSize({200, 200});
    setRect({0, 0, 200, 200});
    _attribute = new char[128];
    std::memset(_attribute, 0, 128);
    _textureId = 0;
}

char *Drawable::getAttribute() const
{
    return _attribute;
}

void Drawable::setAttribute(std::string attribute)
{
    std::memset(_attribute, 0, 128);
    std::memcpy(_attribute, attribute.c_str(), attribute.size());
}

std::tuple<float, float> Drawable::getPosition() const
{
    return _position;
}

void Drawable::setPosition(std::tuple<float, float> position)
{
    _position = position;
}

std::tuple<float, float> Drawable::getSize() const
{
    return _size;
}

void Drawable::setSize(std::tuple<float, float> size)
{
    _size = size;
}

std::tuple<int, int, int, int> Drawable::getRect() const
{
    return _rect;
}

void Drawable::setRect(std::tuple<int, int, int, int> rect)
{
    _rect = rect;
}

std::shared_ptr<Packet> Drawable::getPacket()
{
    auto packet = std::make_shared<Packet>();
    DrawablePacket drawablePacket;
    packet->code = ELEMENT;
    packet->data_size = sizeof(Drawable);
    packet->data = std::malloc(sizeof(Drawable));
    memset(packet->data, 0, sizeof(Drawable));
    drawablePacket.id = _textureId;
    drawablePacket.x = std::get<0>(_position);
    drawablePacket.y = std::get<1>(_position);
    drawablePacket.sizeHorizontal = std::get<0>(_size);
    drawablePacket.sizeVertical = std::get<1>(_size);
    drawablePacket.rectLeft = std::get<0>(_rect);
    drawablePacket.rectTop = std::get<1>(_rect);
    drawablePacket.rectWidth = std::get<2>(_rect);
    drawablePacket.rectHeight = std::get<3>(_rect);
    memcpy(packet->data, &drawablePacket, sizeof(DrawablePacket));
    return packet;
}
