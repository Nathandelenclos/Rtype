/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main.cpp
*/

#include <iostream>
#include <sys/time.h>
#include "../../include/DLLoader.hpp"
#include "../../networking/server/ServerSocket.hpp"

int main() {
    DLLoader loader("../lib_r_type.so");

    IGame *game = loader.getInstance("create");

    ServerSocket serverSocket;

    serverSocket.init_server("127.0.0.1", 6969);

    std::tuple<std::unique_ptr<Packet>, int> packet_client_id;

    std::unique_ptr<Packet> packet;

    std::unique_ptr<Packet> packet_heart_beat = std::make_unique<Packet>();

    timeval receveid_time{};
    timeval current_time{};
    timeval packet_heart_beat_data{};


    while (true) {
        serverSocket.init_fd_set();
        packet_client_id = serverSocket.receive();
        packet = std::move(std::get<0>(packet_client_id));

        if (packet) {
            //use packet
            if (packet->code == HEARTBEAT) {
                gettimeofday(&current_time, nullptr);
                receveid_time = *static_cast<timeval *>(packet->data);
                packet_heart_beat->code = HEARTBEAT;
                packet_heart_beat->data_size = sizeof(timeval);
                packet_heart_beat->data = malloc(packet_heart_beat->data_size);
                timersub(&current_time, &receveid_time, &packet_heart_beat_data);
                std::cout << "Ping: " << packet_heart_beat_data.tv_sec * 1000 + packet_heart_beat_data.tv_usec / 1000 << "ms" << std::endl;
                memcpy(packet_heart_beat->data, &current_time, packet_heart_beat->data_size);
                serverSocket.send(packet_heart_beat.get(), serverSocket.getClientAddress(std::get<1>(packet_client_id)));
            }
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
