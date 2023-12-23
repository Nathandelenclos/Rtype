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
    void receive() override;

    void run() override;

    void listen_server();
    void init_fd_set();

    #ifdef _WIN32
        void read_input();
    #endif

private:
    int sockfd;
    struct sockaddr_in serv_addr;
    std::string lastMessage;
    fd_set _readfds;
    bool loop;
    #ifdef _WIN32
        std::string input;
        std::mutex mtx;
        std::thread inputThread;
        std::unique_ptr<struct timeval> timeout;
    #endif
};

#endif //R_TYPE_SERVER_CLIENTSOCKET_HPP
