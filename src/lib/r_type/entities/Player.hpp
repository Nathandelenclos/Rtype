/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** Player.hpp
*/

#pragma once

#include "Drawable.hpp"
#include "IObject.hpp"
#include <iostream>

class Player : public Drawable, public IObject
{
  public:

    /**
     * @brief Construct a new Player:: Player object
     * @param socket
     */
    explicit Player(ServerSocket *socket);

    /**
     * @brief Destroy the Player:: Player object
     */
    ~Player() override = default;

    /**
     * @brief getPacket, get the packet
     * @return packet (Packet *)
     */
    [[nodiscard]] Packet *getPacket() override;


    /**
     * @brief draw, draw the player
     */
    void draw() override;

  private:
    ServerSocket *socket;
    timeval _annimationTime{};
    float _positionX;
    float _positionY;
    float _direction;
};
