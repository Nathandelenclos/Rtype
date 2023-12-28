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

    while (true) {
        for (auto service: game->getServices()) {
            service->update(game->getObjects());
        }
    }

    return 0;
}
