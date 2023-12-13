//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_SERVERSOCKET_HPP
#define R_TYPE_SERVER_SERVERSOCKET_HPP

#include <string>
#include "../shared/USocket.hpp"


class ServerSocket : public USocket {
public:
    void connect(const std::string& ip, int port) override {
        // Implémentation pour le serveur
    }

    void send(const std::string& message) override {
        // Implémentation pour le serveur
    }

    void receive() override {
        // Implémentation pour le serveur
    }
};


#endif //R_TYPE_SERVER_SERVERSOCKET_HPP
