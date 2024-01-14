/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "ServerSocket.hpp"
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    ServerSocket serverSocket;
    std::cout << "ServerSocket created" << std::endl;
    serverSocket.init_server("127.0.0.1", 6969);

    serverSocket.run();
}
