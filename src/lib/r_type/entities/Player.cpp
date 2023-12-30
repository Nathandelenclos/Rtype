/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Player.cpp
*/

#include "Player.hpp"

void Player::draw() {
    //std::cout << "Player::draw()" << std::endl;
}

Packet *Player::getPacket() const {
    auto *packet = new Packet();
    auto *element = new Element();
    element->x = 0;
    element->y = 0;
    element->width = 0;
    element->height = 0;
    element->type = PLAYER;

    packet->code = ELEMENT;
    packet->data_size = sizeof(Element);
    packet->data = element;
    return packet;
}
