/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main.cpp
*/

#include <iostream>
#include "Server.hpp"

int main() {
    Server server("127.0.0.1", 4242);
    server.run();
    return 0;
}
