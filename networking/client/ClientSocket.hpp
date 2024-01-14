//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_CLIENTSOCKET_HPP
#define R_TYPE_SERVER_CLIENTSOCKET_HPP

#include <cstring>
#include <mutex>
#include <netinet/in.h>
#include <string>
#include <thread>
#include <vector>

#include "networking/shared/USocket.hpp"

class ClientSocket : public USocket
{
  public:
    ClientSocket();
    ~ClientSocket() override;

    bool init_client(const std::string &ip, int port);
    void send(Packet *packet, struct sockaddr_in dest) override;
    void sendPacket(SplitPacket *packet, struct sockaddr_in dest) override;
    std::tuple<std::unique_ptr<Packet>, int> receive() override;

    void run() override;

    std::tuple<std::unique_ptr<Packet>, int> listen_server();
    void init_fd_set();

    bool isInit() const;
    void setInit(bool init);

    void splitAndSend(Packet *packet, struct sockaddr_in dest) override;

    void receivePacketAndAddToBuffer();
    std::unique_ptr<Packet> getPacketFromBuffer();

#ifdef _WIN32
    void read_input();
#endif

    struct sockaddr_in serv_addr;
    int sockfd;

  private:
    std::string lastMessage;
    fd_set _readfds;
    bool loop;
    std::unique_ptr<struct timeval> timeout;
    bool _isInit;
    std::vector<std::tuple<std::unique_ptr<SplitPacket>, timeval>> _packetBuffer;
#ifdef _WIN32
    std::string input;
    std::mutex mtx;
    std::thread inputThread;
#endif
};

#endif // R_TYPE_SERVER_CLIENTSOCKET_HPP
