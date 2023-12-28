/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main.cpp
*/

#include <iostream>
#include "DLLoader.hpp"

int main() {
    DLLoader loader("../test_lib_r_type.so");

    IGame *game = loader.getInstance("create");

    while (true) {
        for (auto service: game->getServices()) {
            service->update(game->getObjects());
        }
    }

    return 0;
}
