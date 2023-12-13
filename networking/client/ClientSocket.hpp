//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_CLIENTSOCKET_HPP
#define R_TYPE_SERVER_CLIENTSOCKET_HPP

#include <string>
#include "../shared/USocket.hpp"


class ClientSocket : public USocket {
public:
    void connect(const std::string& ip, int port) override {
        // Implémentation pour le client
    }

    void send(const std::string& message) override {
        // Implémentation pour le client
    }

    void receive() override {
        // Implémentation pour le client
    }
};


#endif //R_TYPE_SERVER_CLIENTSOCKET_HPP
