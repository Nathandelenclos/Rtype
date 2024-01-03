/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Player.cpp
*/

#include "Player.hpp"

Player::Player(ServerSocket *socket) : socket(socket) {
}

void Player::draw() {
    Packet *packet = getPacket();
    for (auto &client : socket->getClients())
        socket->send(packet, std::get<1>(client));
}

Packet *Player::getPacket() const {
    std::unique_ptr<Packet> packet = std::make_unique<Packet>();
    std::unique_ptr<Element> element = std::make_unique<Element>();
    element->x = 100;
    element->y = 100;
    element->width = 1;
    element->height = 1;
    element->type = PLAYER;

    packet->code = ELEMENT;
    packet->data_size = sizeof(Element);
    packet->data = malloc(packet->data_size);
    memcpy(packet->data, element.get(), packet->data_size);
    return packet.release();
}
