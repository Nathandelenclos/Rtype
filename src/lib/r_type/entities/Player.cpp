/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(ServerSocket *socket) :
    socket(socket)
{
    gettimeofday(&_annimationTime, nullptr);
    _positionX = 100;
    _positionY = 100;
    _direction = 0.1;
}

void Player::draw()
{
    Packet *packet;
    timeval now{};
    timeval diff{};

    gettimeofday(&now, nullptr);
    timersub(&now, &_annimationTime, &diff);
    if (_positionX + 200 >= 800)
        _direction = -0.1;
    if (_positionX <= 0)
        _direction = 0.1;
    if (diff.tv_usec > 100) {
        _positionX += _direction;
        _annimationTime = now;
        packet = getPacket();
        for (auto &client : socket->getClients())
            socket->send(packet, std::get<1>(client));
    }
}

Packet *Player::getPacket()
{
    std::unique_ptr<Packet> packet = std::make_unique<Packet>();
    std::unique_ptr<Element> element = std::make_unique<Element>();

    element->x = _positionX;
    element->y = _positionY;
    element->width = 1;
    element->height = 1;
    element->type = PLAYER;

    packet->code = ELEMENT;
    packet->data_size = sizeof(Element);
    packet->data = malloc(packet->data_size);
    memcpy(packet->data, element.get(), packet->data_size);
    return packet.release();
}
