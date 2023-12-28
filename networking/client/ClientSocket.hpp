//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_CLIENTSOCKET_HPP
#define R_TYPE_SERVER_CLIENTSOCKET_HPP

#include <string>
#include <cstring>
#include <mutex>
#include <thread>
#include "../shared/USocket.hpp"

class ClientSocket : public USocket {
public:
    ClientSocket();
    ~ClientSocket() override;

    void init_client(std::string ip, int port);
    void send(Packet *packet, struct sockaddr_in dest) override;
    std::tuple<std::unique_ptr<Packet>, int> receive() override;

    void run() override;

    std::tuple<std::unique_ptr<Packet>, int> listen_server();
    void init_fd_set();

    #ifdef _WIN32
        void read_input();
    #endif

    struct sockaddr_in serv_addr;
private:
    int sockfd;
    std::string lastMessage;
    fd_set _readfds;
    bool loop;
    std::unique_ptr<struct timeval> timeout;
    #ifdef _WIN32
        std::string input;
        std::mutex mtx;
        std::thread inputThread;
    #endif
};

#endif //R_TYPE_SERVER_CLIENTSOCKET_HPP
