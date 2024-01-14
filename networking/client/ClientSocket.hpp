/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

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
    /**
     * @brief Constructor of ClientSocket
     */
    ClientSocket();

    /**
     * @brief Destructor of ClientSocket
     */
    ~ClientSocket() override;

    /**
     * @brief Init the client socket
     * @param ip
     * @param port
     * @return true if the client is init
     */
    bool init_client(const std::string &ip, int port);

    /**
     * @brief Send a packet to the server
     * @param packet
     * @param dest
     */
    void send(Packet *packet, struct sockaddr_in dest) override;

    /**
     * @brief Send a split packet to the server
     * @param packet
     * @param dest
     */
    void sendPacket(SplitPacket *packet, struct sockaddr_in dest) override;

    /**
     * @brief Receive a packet from the server
     * @return a tuple with the packet and the size of the packet
     */
    std::tuple<std::unique_ptr<Packet>, int> receive() override;

    /**
     * @brief Run the client socket
     */
    void run() override;

    /**
     * @brief Stop the client socket
     */
    std::tuple<std::unique_ptr<Packet>, int> listen_server();

    /**
     * @brief Stop the client socket
     */
    void init_fd_set();

    /**
     * @brief isInit, check if the client is init
     * @return true if the client is init
     */
    bool isInit() const;

    /**
     * @brief setInit, set the client init
     * @param init
     */
    void setInit(bool init);

    /**
     * @brief split and send a packet to the server
     * @param packet
     * @param dest
     */
    void splitAndSend(Packet *packet, struct sockaddr_in dest) override;

    /**
     * @brief receiivePacketAndAddToBuffer receive a packet and add it to the buffer
     */
    void receivePacketAndAddToBuffer();

    /**
     * @brief getPacketFromBuffer get a packet from the buffer
     * @return a packet get from the buffer
     */
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
