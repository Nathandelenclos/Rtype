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

    /**
     * @brief Construct a new Drawable:: Drawable object
     */
    Drawable();

    /**
     * @brief getAttribute, get the attribute
     *
     * @return attribute (char *)
     */
    [[nodiscard]] char *getAttribute() const;

    /**
     * @brief setAttribute, set the attribute
     *
     * @param attribute
     */
    void setAttribute(std::string attribute);


    /**
     * @brief getPosition, get the position
     *
     * @return position (std::tuple<float, float>)
     */
    [[nodiscard]] Position getPosition() const;

    /**
     * @brief setPosition, set the position
     *
     * @param position
     */
    void setPosition(std::tuple<float, float> position);


    /**
     * @brief getSize, get the size
     *
     * @return size (std::tuple<float, float>)
     */
    [[nodiscard]] Size getSize() const;

    /**
     * @brief setSize, set the size
     *
     * @param size
     */
    void setSize(std::tuple<float, float> size);

    /**
     * @brief getScale, get the scale
     *
     * @return scale (float)
     */
    [[nodiscard]] float getScale() const;

    /**
     * @brief setScale, set the scale
     *
     * @param scale
     */
    void setScale(float scale);


    /**
     * @brief getRect, get the rect
     *
     * @return rect (std::tuple<int, int, int, int>)
     */
    [[nodiscard]] Rect getRect() const;

    /**
     * @brief setRect, set the rect
     *
     * @param rect
     */
    void setRect(std::tuple<int, int, int, int> rect);


    /**
     * @brief getPacket, get the packet
     *
     * @return packet (std::shared_ptr<Packet>)
     */
    [[nodiscard]]
    std::shared_ptr<Packet> getPacket();


    /**
     * @brief setHasChanged, set if the drawable has changed
     *
     * @param hasChanged
     */
    void setHasChanged(bool hasChanged);

    /**
     * @brief getHasChanged, get if the drawable has changed
     *
     * @return hasChanged (bool)
     */
    [[nodiscard]]
    bool getHasChanged() const;


    /**
     * @brief addDrawableCollision, add a drawable collision
     *
     * @param drawableCollision
     */
    void addDrawableCollision(std::shared_ptr<Drawable> drawableCollision);

    /**
     * @brief getDrawablesCollision, get the drawables collision
     *
     * @return drawablesCollision (std::vector<std::shared_ptr<Drawable>>)
     */
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