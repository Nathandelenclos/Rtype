/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Drawable.cpp
*/

#include "Drawable.hpp"

#include <cstring>
#include <utility>

/**
 * @brief Construct a new Drawable:: Drawable object
 */
Drawable::Drawable()
{
    setPosition({0, 0});
    setSize({200, 200});
    setRect({0, 0, 200, 200});
    _attribute = new char[64];
    std::memset(_attribute, 0, 64);
    _textureId = 0;
}

/**
 * @brief getAttribute, get the attribute
 * @return attribute (char *)
 */
char *Drawable::getAttribute() const
{
    return _attribute;
}

/**
 * @brief setAttribute, set the attribute
 * @param attribute
 */
void Drawable::setAttribute(std::string attribute)
{
    std::memset(_attribute, 0, 64);
    std::memcpy(_attribute, attribute.c_str(), attribute.size());
    std::cout << "attribute: " << _attribute << std::endl;
    hasChanged = true;
}

/**
 * @brief setAttribute, set the attribute
 * @param attribute (srd::tuple<float, float>)
 */
std::tuple<float, float> Drawable::getPosition() const
{
    return _position;
}

/**
 * @brief setPosition, set the position
 * @param position
 */
void Drawable::setPosition(std::tuple<float, float> position)
{
    _position = position;
    hasChanged = true;
}

/**
 * @brief getSize, get the size
 * @return size (std::tuple<float, float>)
 */
std::tuple<float, float> Drawable::getSize() const
{
    return _size;
}

/**
 * @brief getScale, get the scale
 * @return scale (float)
 */
float Drawable::getScale() const
{
    return _scale;
}

/**
 * @brief setSize, set the size
 * @param size
 */
void Drawable::setSize(std::tuple<float, float> size)
{
    _size = size;
    hasChanged = true;
}

/**
 * @brief setScale, set the scale
 */
void Drawable::setScale(float scale)
{
    _scale = scale;
}

/**
 * @brief getRect, get the rect
 * @return rect (std::tuple<int, int, int, int>)
 */
std::tuple<int, int, int, int> Drawable::getRect() const
{
    return _rect;
}

/**
 * @brief setRect, set the rect
 * @param rect
 */
void Drawable::setRect(std::tuple<int, int, int, int> rect)
{
    _rect = rect;
    hasChanged = true;
}

/**
 * @brief getPacket, get the packet
 * @return packet (std::shared_ptr<Packet>)
 */
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
    std::memcpy(&drawablePacket.attribute, _attribute, 8);
    std::memcpy(&drawablePacket.attribute2, _attribute + 8, 8);
    memcpy(packet->data, &drawablePacket, sizeof(DrawablePacket));
    return packet;
}

/**
 * @brief setHasChanged, set if the drawable has changed
 * @param hasChanged
 */
void Drawable::setHasChanged(bool hasChanged)
{
    this->hasChanged = hasChanged;
}

/**
 * @brief getHasChanged, get if the drawable has changed
 * @return hasChanged (bool)
 */
bool Drawable::getHasChanged() const
{
    return hasChanged;
}

/**
 * @brief addDrawableCollision, add a drawable collision
 * @param drawableCollision
 */
void Drawable::addDrawableCollision(std::shared_ptr<Drawable> drawableCollision)
{
    _drawablesCollision.push_back(std::move(drawableCollision));
}

/**
 * @brief getDrawablesCollision, get the drawables collision
 * @return drawablesCollision (std::vector<std::shared_ptr<Drawable>>)
 */
std::vector<std::shared_ptr<Drawable>> Drawable::getDrawablesCollision() const
{
    return _drawablesCollision;
}
