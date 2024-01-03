/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main.cpp
*/

#include <iostream>
#include "Server.hpp"

int main() {
    Server server("10.17.72.28", 4242);
    server.run();
    return 0;
}
