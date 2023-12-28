/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main.cpp
*/

#include "../../networking/client/ClientSocket.hpp"
#include <iostream>

int main()
{
    ClientSocket clientSocket;

    clientSocket.init_client("127.0.0.1", 6969);

    std::tuple<std::unique_ptr<Packet>, int> packet_client_id;

    std::unique_ptr<Packet> packet;

    while (true) {
        std::cout << "ClientSocket run" << std::endl;
        clientSocket.init_fd_set();
        packet_client_id = clientSocket.receive();
        packet = std::move(std::get<0>(packet_client_id));

        if (packet) {
            //use packet
            std::cout << "Packet received from server " << std::get<1>(packet_client_id) << std::endl;
            //destroy packet
            packet.reset();
            packet_client_id = std::tuple<std::unique_ptr<Packet>, int>(nullptr, 0);
        }
    }
}