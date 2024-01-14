/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "ClientSocket.hpp"
#include <iostream>

int main()
{
    ClientSocket clientSocket;

    clientSocket.init_client("127.0.0.1", 6969);

    clientSocket.run();
}
