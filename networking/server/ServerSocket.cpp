#include "ServerSocket.hpp"
#include <stdexcept>
#include <iostream>

ServerSocket::ServerSocket() {
    std::cout << "ServerSocket constructor" << std::endl;

    #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
            std::cout << "WSAStartup failed: " << WSAGetLastError() << std::endl;
            throw std::runtime_error("Failed to initialize Winsock");
        }
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd == INVALID_SOCKET) {
            std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
            WSACleanup();
            throw std::runtime_error("Failed to create socket");
        }
    #elif defined(__unix__) || defined(__unix__)
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0) {
            std::cout << "Error sockfd < 0 sockfd : " << sockfd << std::endl;
            throw std::runtime_error("Failed to create socket");
        }
    #endif
    timeout = std::make_unique<struct timeval>();
    timeout->tv_sec = 0;
    timeout->tv_usec = 1;
    std::cout << "Socket created successfully (fd: " << sockfd << ")" << std::endl;
}

ServerSocket::~ServerSocket() {
    #ifdef _WIN32
        closesocket(sockfd);
    #elif defined(__unix__) || defined(__unix__)
        close(sockfd);
    #endif
}

void ServerSocket::init_server(std::string ip, int port) {
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address");
    }
    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        throw std::runtime_error("Failed to bind socket");
    }
}

void ServerSocket::send(Packet *packet, struct sockaddr_in client) {
    splitAndSend(packet, client);
}

void ServerSocket::sendPacket(SplitPacket *packet, struct sockaddr_in dest) {
    char *buffer = static_cast<char *>(malloc(sizeof(SplitPacket)));
    memset(buffer, 0, sizeof(SplitPacket));
    memcpy(buffer, packet, sizeof(SplitPacket));
    if (sendto(sockfd, reinterpret_cast<const char *>(buffer), sizeof(SplitPacket), 0, (struct sockaddr*)&dest, sizeof(dest)) < 0) {
        throw std::runtime_error("Failed to send packet");
    }
    free(buffer);
}

void ServerSocket::addClient(struct sockaddr_in client) {
    int id = 1;
    for (auto& [i, cli, splitPackets, lastReceived] : clients) {
        if (i == id) {
            id++;
        } else {
            break;
        }
    }
    clients.emplace_back(id, client, std::vector<std::tuple<std::shared_ptr<SplitPacket>, timeval>>(), timeval());
}

int ServerSocket::getClientId(struct sockaddr_in client) {
    if (clients.empty()) {
        return -1;
    }
    for (auto& [id, cli, splitPackets, lastReceived] : clients) {
        if (cli.sin_addr.s_addr == client.sin_addr.s_addr && cli.sin_port == client.sin_port) {
            return id;
        }
    }
    return -1;
}

std::tuple<std::unique_ptr<Packet>, int> ServerSocket::receive() {
    receivePacketAndAddToBuffer();
    return manageClientsBuffer();
}


/*std::tuple<std::unique_ptr<Packet>, int> ServerSocket::receive() {
    packet_last.code = UNDEFINED;


    struct sockaddr_in cli_addr_code{};
    socklen_t len_code = sizeof(cli_addr_code);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) < 0) {
        throw std::runtime_error("Failed to read from socket");
    } else if (FD_ISSET(sockfd, &_readfds)) {
        if (recvfrom(sockfd, reinterpret_cast<char *>(&packet_last.code), sizeof(int), 0, (struct sockaddr*)&cli_addr_code, &len_code) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
        if (packet_last.code == UNDEFINED) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        return std::tuple<std::unique_ptr<Packet>, int>(nullptr, 0);
    }

    std::cout << "packet.code: " << packet_last.code << std::endl;
    struct sockaddr_in cli_addr_size{};
    socklen_t len_size = sizeof(cli_addr_size);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) < 0) {
        throw std::runtime_error("Failed to read from socket");
    } else if (FD_ISSET(sockfd, &_readfds)) {
        if (recvfrom(sockfd, reinterpret_cast<char *>(&packet_last.data_size), sizeof(int), 0, (struct sockaddr*)&cli_addr_size, &len_size) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
        if (cli_addr_size.sin_addr.s_addr != cli_addr_code.sin_addr.s_addr || cli_addr_size.sin_port != cli_addr_code.sin_port) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        return std::tuple<std::unique_ptr<Packet>, int>(nullptr, 0);
    }
    std::cout << "packet.data_size: " << packet_last.data_size << std::endl;


    packet_last.data = malloc(packet_last.data_size + 1);
    memset(packet_last.data, 0, packet_last.data_size + 1);
    struct sockaddr_in cli_addr_data{};
    socklen_t len_data = sizeof(cli_addr_data);
    char *buffer = static_cast<char *>(malloc(packet_last.data_size + 1));
    memset(buffer, 0, packet_last.data_size + 1);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) < 0) {
        throw std::runtime_error("Failed to read from socket");
    } else if (FD_ISSET(sockfd, &_readfds)) {
        if (recvfrom(sockfd, buffer, packet_last.data_size, 0, (struct sockaddr*)&cli_addr_data, &len_data) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        free(buffer);
        free(packet_last.data);
        return std::tuple<std::unique_ptr<Packet>, int>(nullptr, 0);
    }
    memcpy(packet_last.data, buffer, packet_last.data_size);

    std::string message = reinterpret_cast<char *>(packet_last.data);
    std::cout << "message: " << message << std::endl;

    int id = getClientId(cli_addr_data);
    if (id == -1) {
        addClient(cli_addr_data);
        id = getClientId(cli_addr_data);
    }


    lastClientAddress = cli_addr_data;
    std::unique_ptr<Packet> cli_addr_packet = std::make_unique<Packet>();
    if (message == "connection") {
        cli_addr_packet->code = MESSAGE;
        cli_addr_packet->data_size = 19;
        cli_addr_packet->data = malloc(19);
        memcpy(cli_addr_packet->data, "connection accepted", 19);
    } else {
        cli_addr_packet->code = MESSAGE;
        cli_addr_packet->data_size = 8;
        cli_addr_packet->data = malloc(8);
        memcpy(cli_addr_packet->data, "received", 8);
    }
    send(cli_addr_packet.get(), cli_addr_data);
    return std::make_tuple(std::move(std::make_unique<Packet>(packet_last)), id);
}*/

void ServerSocket::init_fd_set() {
    FD_ZERO(&_readfds);
    FD_SET(sockfd, &_readfds);
}

void ServerSocket::run() {
    while (true) {
        init_fd_set();
        receive();
        if (lastMessage == "ping") {
            std::unique_ptr<Packet> packet = std::make_unique<Packet>();
            packet->code = MESSAGE;
            packet->data_size = 4;
            packet->data = malloc(4);
            memcpy(packet->data, "pong", 4);
            send(packet.get(), lastClientAddress);
        }
        if (lastMessage == "exit")
            break;
    }
}

std::vector<std::tuple<int, struct sockaddr_in, std::vector<std::tuple<std::shared_ptr<SplitPacket>, timeval>>, timeval>>& ServerSocket::getClients() {
    return clients;
}

struct sockaddr_in ServerSocket::getClientAddress(int id) {
    for (auto& [i, cli, splitPackets, lastReceived] : clients) {
        if (i == id) {
            return cli;
        }
    }
    throw std::runtime_error("Client not found");
}

void ServerSocket::broadcast(Packet *packet) {
    for (auto& [id, cli, splitPackets, lastReceived] : clients) {
        send(packet, cli);
    }
}

void ServerSocket::splitAndSend(Packet *packet, struct sockaddr_in dest) {
    std::unique_ptr<SplitPacket> splitPacket = std::make_unique<SplitPacket>();
    splitPacket->code = packet->code;
    int i;

    if (packet->data_size < 1024) {
        splitPacket->data[0] = '\0';
        splitPacket->packet_id = 0;
        splitPacket->max_packet_id = 0;
        memset(splitPacket->data, 0, 1024);
        memcpy(splitPacket->data, packet->data, packet->data_size);
        sendPacket(splitPacket.get(), dest);
    } else {
        splitPacket->max_packet_id = packet->data_size / 1024 + 1;
        for (i = 0; i < packet->data_size / 1024; i++) {
            splitPacket->packet_id = i;
            memset(splitPacket->data, 0, 1024);
            memcpy(splitPacket->data, (char *)packet->data + i * 1024, 1024);
            sendPacket(splitPacket.get(), dest);
        }
        int rest = packet->data_size % 1024;
        if (rest > 0) {
            splitPacket->packet_id = i + 1;
            memset(splitPacket->data, 0, 1024);
            memcpy(splitPacket->data, (char *)packet->data + i * 1024 + 1, rest);
            sendPacket(splitPacket.get(), dest);
        }
    }
}

void ServerSocket::receivePacketAndAddToBuffer() {
    struct sockaddr_in cli_addr{};

    std::shared_ptr<SplitPacket> packet = std::make_shared<SplitPacket>();
    timeval recvTime{};
    socklen_t len = sizeof(cli_addr);
    char *buffer = static_cast<char *>(malloc(sizeof(SplitPacket)));
    memset(buffer, 0, sizeof(SplitPacket));
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) < 0) {
        free(buffer);
        throw std::runtime_error("Failed to read from socket");
    } else if (FD_ISSET(sockfd, &_readfds)) {
        if (recvfrom(sockfd, buffer, sizeof(SplitPacket), 0, (struct sockaddr*)&cli_addr, &len) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        free(buffer);
        return;
    }

    memcpy(packet.get(), buffer, sizeof(SplitPacket));

    int id = getClientId(cli_addr);
    if (id == -1) {
        addClient(cli_addr);
        id = getClientId(cli_addr);
    }
    for (auto& [i, cli, splitPackets, lastReceived] : clients) {
        if (i == id) {
            gettimeofday(&recvTime, nullptr);
            gettimeofday(&lastReceived, nullptr);
            splitPackets.emplace_back(packet, recvTime);
        }
    }
    free(buffer);
}

std::tuple<std::unique_ptr<Packet>, int> ServerSocket::manageClientsBuffer() {
    std::unique_ptr<Packet> packet = std::make_unique<Packet>();
    int counter = 0;
    long long int size = 0;
    std::unique_ptr<struct timeval> now = std::make_unique<struct timeval>();
    std::unique_ptr<struct timeval> diff = std::make_unique<struct timeval>();

    for (auto& [id, cli, splitPackets, lastReceived] : getClients()) {
        auto it = splitPackets.begin();
        while (it != splitPackets.end()) {
            auto& [splitPacket, recvTime] = *it;
            if (splitPacket->packet_id == 0 && splitPacket->max_packet_id == 0) {
                packet->code = splitPacket->code;
                packet->data_size = splitPacket->max_packet_id * 1024;
                if (packet->data_size == 0) {
                    packet->data_size = 1024;
                }
                packet->data = malloc(packet->data_size);
                memcpy(packet->data, splitPacket->data, packet->data_size);
                it = splitPackets.erase(it);
                return std::make_tuple(std::move(packet), id);
            } else {
                if (splitPacket->packet_id == counter) {
                    counter++;
                    size += strlen(splitPacket->data);
                    if (splitPacket->packet_id == splitPacket->max_packet_id) {
                        packet->code = splitPacket->code;
                        packet->data_size = size;
                        packet->data = malloc(packet->data_size + 1);
                        memset(packet->data, 0, packet->data_size + 1);
                        int counterAssign = 0;
                        auto itAssign = splitPackets.begin();
                        while (itAssign != splitPackets.end()) {
                            auto& [splitPacketAssign, recvTimeAssign] = *itAssign;
                            memcpy((char *)packet->data + counterAssign * 1024, splitPacketAssign->data, strlen(splitPacketAssign->data));
                            counterAssign++;
                            itAssign = splitPackets.erase(itAssign);
                        }
                        return std::make_tuple(std::move(packet), id);
                    }
                } else {
                    counter = 0;
                    size = 0;
                }
            }
            ++it;
        }
    }

    free(packet->data);
    for (auto& [idtimeout, clitimeout, splitPacketstimeout, lastReceivedtimeout] : getClients()) {
        auto ittimeout = splitPacketstimeout.begin();
        while (ittimeout != splitPacketstimeout.end()) {
            auto& [splitPackettimeout, recvTimetimeout] = *ittimeout;
            gettimeofday(now.get(), nullptr);
            timersub(now.get(), &recvTimetimeout, diff.get());
            if (diff->tv_sec > 1) {
                ittimeout = splitPacketstimeout.erase(ittimeout);
            } else {
                ++ittimeout;
            }
        }
    }
    return std::make_tuple(nullptr, 0);
}

void ServerSocket::checkClientsDeconnection() {
    timeval now{};
    timeval diff{};
    gettimeofday(&now, nullptr);
    for (auto& [id, cli, splitPackets, lastReceived] : getClients()) {
        timersub(&now, &lastReceived, &diff);
        if (diff.tv_sec > 1) {
            std::shared_ptr<Packet> packet = std::make_shared<Packet>();
            packet->code = EVENT;
            packet->data_size = strlen("player left");
            packet->data = malloc(packet->data_size);
            memcpy(packet->data, "player left", packet->data_size);
            broadcast(packet.get());
            auto it = getClients().begin();
            while (it != getClients().end()) {
                auto& [iddel, clidel, splitPacketsdel, lastReceiveddel] = *it;
                if (id == iddel) {
                    it = getClients().erase(it);
                } else {
                    ++it;
                }
            }
        }
    }
}
