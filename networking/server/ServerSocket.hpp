//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_SERVERSOCKET_HPP
#define R_TYPE_SERVER_SERVERSOCKET_HPP

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <vector>
#include <arpa/inet.h>
#include "../shared/USocket.hpp"

class ServerSocket : public USocket {
public:
    ServerSocket();
    ~ServerSocket();

    void init_server(std::string ip, int port);
    void send(const std::string& message) override;
    void receive() override;

    void run() override;

private:
    int sockfd;
    struct sockaddr_in serv_addr;
    std::string lastMessage;
    // store clients
    std::vector<struct sockaddr_in> clients;
    struct sockaddr_in lastClientAddress;

};

#endif //R_TYPE_SERVER_SERVERSOCKET_HPP
