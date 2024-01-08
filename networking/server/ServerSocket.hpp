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
#include <netinet/in.h>
#include "../shared/USocket.hpp"

class ServerSocket : public USocket {
public:
    ServerSocket();
    ~ServerSocket() override;

    void init_server(int port);
    void send(Packet *packet, struct sockaddr_in dest) override;
    void sendPacket(SplitPacket *packet, struct sockaddr_in dest) override;
    void broadcast(Packet *packet);
    std::tuple<std::unique_ptr<Packet>, int> receive() override;

    void run() override;
    void addClient(struct sockaddr_in client);
    int getClientId(sockaddr_in client);
    struct sockaddr_in getClientAddress(int id);

    void init_fd_set();

    void splitAndSend(Packet *packet, struct sockaddr_in dest) override;
    void receivePacketAndAddToBuffer();


    [[nodiscard]] std::vector<std::tuple<int, struct sockaddr_in, std::vector<std::tuple<std::shared_ptr<SplitPacket>, timeval>>, timeval>>& getClients();

    std::tuple<std::unique_ptr<Packet>, int> manageClientsBuffer();

    void setNewClientConnected(int newClientConnected);
    int getNewClientId();
    int checkClientsDeconnection();

private:
    unsigned long long sockfd;
    struct sockaddr_in serv_addr{};
    std::string lastMessage;
    std::vector<std::tuple<int, struct sockaddr_in, std::vector<std::tuple<std::shared_ptr<SplitPacket>, timeval>>, timeval>> clients;
    struct sockaddr_in lastClientAddress{};
    std::unique_ptr<struct timeval> timeout;
    fd_set _readfds;
    bool newClientConnected;
    int newClientId;
};

#endif //R_TYPE_SERVER_SERVERSOCKET_HPP
