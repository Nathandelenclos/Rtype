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
    std::cout << "ClientSocket send" << std::endl;
    char *buffer = static_cast<char *>(malloc(packet->data_size + 1));
    memset(buffer, 0, packet->data_size + 1);
    memcpy(buffer, packet->data, packet->data_size);
    std::string message = buffer;
    std::cout << "message: " << message << std::endl;
    if (sendto(sockfd, reinterpret_cast<const char *>(&packet->code), sizeof(int), 0, (struct sockaddr*)&client, sizeof(client)) < 0) {
        throw std::runtime_error("Failed to send message");
    }
    if (sendto(sockfd, reinterpret_cast<const char *>(&packet->data_size), sizeof(int), 0, (struct sockaddr*)&client, sizeof(client)) < 0) {
        throw std::runtime_error("Failed to send message");
    }
    if (sendto(sockfd, reinterpret_cast<const char *>(packet->data), packet->data_size, 0, (struct sockaddr*)&client, sizeof(client)) < 0) {
        throw std::runtime_error("Failed to send message");
    }
}

void ServerSocket::addClient(struct sockaddr_in client) {
    int id = 1;
    while (clients.find(id) != clients.end()) {
        id++;
    }
    clients[id] = client;
}

int ServerSocket::getClientId(struct sockaddr_in client) {
    for (auto& [id, cli] : clients) {
        if (cli.sin_addr.s_addr == client.sin_addr.s_addr && cli.sin_port == client.sin_port) {
            return id;
        }
    }
    return -1;
}


std::tuple<std::unique_ptr<Packet>, int> ServerSocket::receive() {
    Packet packet{};
    packet.code = UNDEFINED;


    struct sockaddr_in cli_addr_code{};
    socklen_t len_code = sizeof(cli_addr_code);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) < 0) {
        throw std::runtime_error("Failed to read from socket");
    } else if (FD_ISSET(sockfd, &_readfds)) {
        if (recvfrom(sockfd, reinterpret_cast<char *>(&packet.code), sizeof(int), 0, (struct sockaddr*)&cli_addr_code, &len_code) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
        if (packet.code == UNDEFINED) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        return std::tuple<std::unique_ptr<Packet>, int>(nullptr, 0);
    }

    std::cout << "packet.code: " << packet.code << std::endl;
    struct sockaddr_in cli_addr_size{};
    socklen_t len_size = sizeof(cli_addr_size);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) < 0) {
        throw std::runtime_error("Failed to read from socket");
    } else if (FD_ISSET(sockfd, &_readfds)) {
        if (recvfrom(sockfd, reinterpret_cast<char *>(&packet.data_size), sizeof(int), 0, (struct sockaddr*)&cli_addr_size, &len_size) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
        if (cli_addr_size.sin_addr.s_addr != cli_addr_code.sin_addr.s_addr || cli_addr_size.sin_port != cli_addr_code.sin_port) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        return std::tuple<std::unique_ptr<Packet>, int>(nullptr, 0);
    }
    std::cout << "packet.data_size: " << packet.data_size << std::endl;


    packet.data = malloc(packet.data_size + 1);
    memset(packet.data, 0, packet.data_size + 1);
    struct sockaddr_in cli_addr_data{};
    socklen_t len_data = sizeof(cli_addr_data);
    char *buffer = static_cast<char *>(malloc(packet.data_size + 1));
    memset(buffer, 0, packet.data_size + 1);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) < 0) {
        throw std::runtime_error("Failed to read from socket");
    } else if (FD_ISSET(sockfd, &_readfds)) {
        if (recvfrom(sockfd, buffer, packet.data_size, 0, (struct sockaddr*)&cli_addr_data, &len_data) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        free(buffer);
        free(packet.data);
        return std::tuple<std::unique_ptr<Packet>, int>(nullptr, 0);
    }
    memcpy(packet.data, buffer, packet.data_size);

    std::string message = reinterpret_cast<char *>(packet.data);
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
    return std::make_tuple(std::move(std::make_unique<Packet>(packet)), id);
}

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

std::map<int, struct sockaddr_in> ServerSocket::getClients() const {
    return clients;
}

struct sockaddr_in ServerSocket::getClientAddress(int id) {
    return clients[id];
}