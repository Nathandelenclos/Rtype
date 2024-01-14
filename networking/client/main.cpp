//
// Created by talleux on 12/18/23.
//

#include "ClientSocket.hpp"
#include <iostream>

int main()
{
    ClientSocket clientSocket;

    clientSocket.init_client("127.0.0.1", 6969);

    clientSocket.run();
}
