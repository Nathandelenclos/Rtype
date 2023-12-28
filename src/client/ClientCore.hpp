//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include "../../networking/client/ClientSocket.hpp"

class ClientCore {
    public:
        ClientCore();
        ~ClientCore() = default;
        void run();

        bool init_socket(std::string ip, int port);

    private:
        std::unique_ptr<ClientSocket> _socket;
};
