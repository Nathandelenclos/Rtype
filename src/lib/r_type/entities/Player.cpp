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
    std::unique_ptr<Packet> packet = std::make_unique<Packet>();
    std::unique_ptr<Element> element = std::make_unique<Element>();
    element->x = 0;
    element->y = 0;
    element->width = 0;
    element->height = 0;
    element->type = PLAYER;

    packet->code = ELEMENT;
    packet->data_size = sizeof(Element);
    packet->data = malloc(packet->data_size);
    memcpy(packet->data, element.get(), packet->data_size);
    return packet.release();
}
