/*
** EPITECH PROJECT, 2023
** RType
** File description:
** main.cpp
*/

#include "Server.hpp"
#include <iostream>

int main(int ac, char **av)
{
    int port = av[1] ? atoi(av[1]) : 4242;
    Server server(port);
    server.run();
    return 0;
}
