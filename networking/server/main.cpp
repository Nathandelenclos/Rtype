//
// Created by talleux on 12/18/23.
//

#include <iostream>
#include "ServerSocket.hpp"

int main() {
    ServerSocket serverSocket;

    serverSocket.init_server("127.0.0.1", 6969);

    serverSocket.run();
}
