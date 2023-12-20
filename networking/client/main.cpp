//
// Created by talleux on 12/18/23.
//

#include <iostream>
#include "ClientSocket.hpp"

int main() {
    ClientSocket clientSocket;

    clientSocket.init_client("127.0.0.1", 6969);

    clientSocket.run();
}
