//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_SERVERSOCKET_HPP
#define R_TYPE_SERVER_SERVERSOCKET_HPP

#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <memory>
#include "../shared/USocket.hpp"

class ServerSocket : public USocket {
public:
    ServerSocket();
    ~ServerSocket() override;

    void init_server(std::string ip, int port);
    void send(Packet *packet, struct sockaddr_in dest) override;
    std::unique_ptr<Packet> receive() override;

    void run() override;
    void addClient(struct sockaddr_in client);
    int getClientId(sockaddr_in client);


private:
    unsigned long long sockfd;
    struct sockaddr_in serv_addr{};
    std::string lastMessage;
    std::map<int, struct sockaddr_in> clients;
    struct sockaddr_in lastClientAddress{};
};

#endif //R_TYPE_SERVER_SERVERSOCKET_HPP
