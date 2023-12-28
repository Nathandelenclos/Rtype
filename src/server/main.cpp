/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main.cpp
*/

#include <iostream>
#include "../../include/DLLoader.hpp"
#include "../../networking/server/ServerSocket.hpp"

int main() {
    DLLoader loader("../lib_r_type.so");

    IGame *game = loader.getInstance("create");

    ServerSocket serverSocket;

    serverSocket.init_server("127.0.0.1", 6969);

    std::tuple<std::unique_ptr<Packet>, int> packet_client_id;

    std::unique_ptr<Packet> packet;

    while (true) {
        packet_client_id = serverSocket.receive();
        packet = std::move(std::get<0>(packet_client_id));

        if (packet) {
            //use packet
            std::cout << "Packet received from client " << std::get<1>(packet_client_id) << std::endl;
            //destroy packet
            packet.reset();
            packet_client_id = std::tuple<std::unique_ptr<Packet>, int>(nullptr, 0);
        }

        for (auto service: game->getServices()) {
            service->update(game->getObjects());
        }
    }

    return 0;
}
