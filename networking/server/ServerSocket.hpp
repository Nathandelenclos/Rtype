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
    void broadcast(Packet *packet);
    std::tuple<std::unique_ptr<Packet>, int> receive() override;

    void run() override;
    void addClient(struct sockaddr_in client);
    int getClientId(sockaddr_in client);
    struct sockaddr_in getClientAddress(int id);

    void init_fd_set();

    [[nodiscard]] std::map<int, struct sockaddr_in> getClients() const;

    std::string test = "test";
private:
    unsigned long long sockfd;
    struct sockaddr_in serv_addr{};
    std::string lastMessage;
    std::map<int, struct sockaddr_in> clients;
    struct sockaddr_in lastClientAddress{};
    std::unique_ptr<struct timeval> timeout;
    fd_set _readfds;
};

#endif //R_TYPE_SERVER_SERVERSOCKET_HPP
