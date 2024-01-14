/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#ifndef R_TYPE_SERVER_SERVERSOCKET_HPP
#define R_TYPE_SERVER_SERVERSOCKET_HPP

#include "../shared/USocket.hpp"
#include <cstring>
#include <map>
#include <memory>
#include <netinet/in.h>
#include <string>
#include <vector>

class ServerSocket : public USocket
{
  public:

    /**
     * @brief Constructor of ServerSocket
     */
    ServerSocket();

    /**
     * @brief Destructor of ServerSocket
     */
    ~ServerSocket() override;

    /**
     * @brief Init the server socket
     * @param port
     */
    void init_server(int port);

    /**
     * @brief Send a packet to a client
     * @param packet
     * @param dest
     */
    void send(Packet *packet, struct sockaddr_in dest) override;

    /**
     * @brief Send a split packet to a client
     * @param packet
     * @param dest
     */
    void sendPacket(SplitPacket *packet, struct sockaddr_in dest) override;

    /**
     * @brief Broadcast a packet to all clients
     * @param packet
     */
    void broadcast(Packet *packet);

    /**
     * @brief Receive a packet from a client
     * @return a tuple with the packet and the size of the packet
     */
    std::tuple<std::unique_ptr<Packet>, int> receive() override;

    /**
     * @brief Run the server socket
     */
    void run() override;

    /**
     * @brief Add a client to the server
     * @param client
     */
    void addClient(struct sockaddr_in client);

    /**
     * @brief Remove a client from the server
     * @param client
     */
    int getClientId(sockaddr_in client);

    /**
     * @brief Get the client address
     * @param id
     * @return the client address
     */
    struct sockaddr_in getClientAddress(int id);

    /**
     * @brief init_fd_set, init the fd_set
     */
    void init_fd_set();

    /**
     * @brief split and send a packet to a client
     * @param packet
     * @param dest
     */
    void splitAndSend(Packet *packet, struct sockaddr_in dest) override;

    /**
     * @brief receivePacketAndAddToBuffer, receive a packet and add it to the buffer
     */
    void receivePacketAndAddToBuffer();

    /**
     * @brief getClients, get the clients
     * @return a tuple with the client id, the client address, the client buffer and the client timeout
     */
    [[nodiscard]] std::vector<
        std::tuple<int, struct sockaddr_in, std::vector<std::tuple<std::shared_ptr<SplitPacket>, timeval>>, timeval>> &
    getClients();

    /**
     * @brief manageClientsBuffer, manage the clients buffer
     * @return a tuple with the packet and the size of the packet
     */
    std::tuple<std::unique_ptr<Packet>, int> manageClientsBuffer();

    /**
     * @brief setNewClientConnected, set the new client connected
     * @param newClientConnected
     */
    void setNewClientConnected(int newClientConnected);

    /**
     * @brief getNewClientId, get the new client id
     */
    int getNewClientId();

    /**
     * @brief checkClientsDeconnection, check if a client is disconnected
     * @return the client id
     */
    int checkClientsDeconnection();

    /**
     * @brief clientDump, dump the clients
     */
    void clientDump();

  private:
    unsigned long long sockfd;
    struct sockaddr_in serv_addr {
    };
    std::string lastMessage;
    std::vector<
        std::tuple<int, struct sockaddr_in, std::vector<std::tuple<std::shared_ptr<SplitPacket>, timeval>>, timeval>>
        clients;
    struct sockaddr_in lastClientAddress {
    };
    std::unique_ptr<struct timeval> timeout;
    fd_set _readfds;
    bool newClientConnected;
    int newClientId;
    int nextClientId = 1;
};

#endif // R_TYPE_SERVER_SERVERSOCKET_HPP
