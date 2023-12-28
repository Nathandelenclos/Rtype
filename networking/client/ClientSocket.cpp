//
// Created by talleux on 12/13/23.
//

#include "ClientSocket.hpp"
#include <stdexcept>
#include <iostream>

ClientSocket::ClientSocket() {
    std::cout << "ClientSocket constructor" << std::endl;

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

    loop = true;

    std::cout << "Socket created successfully (fd: " << sockfd << ")" << std::endl;
}

ClientSocket::~ClientSocket() {
    #ifdef _WIN32
        closesocket(sockfd);
    #elif defined(__unix__) || defined(__unix__)
        close(sockfd);
    #endif
}

bool ClientSocket::init_client(const std::string& ip, int port) {
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        return false;
    }
    return true;
}

void ClientSocket::send(Packet *packet, struct sockaddr_in dest) {
    if (sendto(sockfd, reinterpret_cast<const char *>(&packet->code), sizeof(int), 0, (struct sockaddr*)&dest, sizeof(dest)) < 0) {
        throw std::runtime_error("Failed to send message");
    }
    if (sendto(sockfd, reinterpret_cast<const char *>(&packet->data_size), sizeof(int), 0, (struct sockaddr*)&dest, sizeof(dest)) < 0) {
        throw std::runtime_error("Failed to send message");
    }
    char *buffer = static_cast<char *>(packet->data);
    if (sendto(sockfd, buffer, packet->data_size, 0, (struct sockaddr*)&dest, sizeof(dest)) < 0) {
        throw std::runtime_error("Failed to send message");
    }
}

std::tuple<std::unique_ptr<Packet>, int> ClientSocket::receive() {
    Packet packet{};
    packet.code = UNDEFINED;
    struct sockaddr_in cli_addr_code{};
    socklen_t len_code = sizeof(cli_addr_code);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) > 0) {
        if (recvfrom(sockfd, reinterpret_cast<char *>(&packet.code), sizeof(int), 0, (struct sockaddr*)&cli_addr_code, &len_code) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
        if (packet.code == UNDEFINED) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        return std::make_tuple(nullptr, 0);
    }


    struct sockaddr_in cli_addr_size{};
    socklen_t len_size = sizeof(cli_addr_size);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) > 0) {
        if (recvfrom(sockfd, reinterpret_cast<char *>(&packet.data_size), sizeof(int), 0, (struct sockaddr*)&cli_addr_size, &len_size) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
        if (cli_addr_size.sin_addr.s_addr != cli_addr_code.sin_addr.s_addr || cli_addr_size.sin_port != cli_addr_code.sin_port) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        return std::make_tuple(nullptr, 0);
    }


    packet.data = malloc(packet.data_size + 1);
    memset(packet.data, 0, packet.data_size + 1);
    struct sockaddr_in cli_addr_data{};
    socklen_t len_data = sizeof(cli_addr_data);
    char *buffer = static_cast<char *>(malloc(packet.data_size + 1));
    memset(buffer, 0, packet.data_size + 1);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) > 0) {
        if (recvfrom(sockfd, buffer, packet.data_size, 0, (struct sockaddr*)&cli_addr_data, &len_data) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        free(buffer);
        free(packet.data);
        return std::make_tuple(nullptr, 0);
    }
    memcpy(packet.data, buffer, packet.data_size);


    std::string message = reinterpret_cast<char *>(packet.data);
    if (message == "received") {
        std::cout << "(Ghost Mode) Received message from " << inet_ntoa(cli_addr_data.sin_addr) << ":" << ntohs(cli_addr_data.sin_port) << std::endl;
        return std::make_tuple(nullptr, 0);
    }
    lastMessage = message;
    return std::make_tuple(std::make_unique<Packet>(packet), -1);
}

#ifdef _WIN32
    void ClientSocket::read_input() {
        while (loop) {
            std::string message;
            std::getline(std::cin, message);
            {
                std::lock_guard<std::mutex> lock(mtx);
                input = message;
            }
        }
    }
#endif

void ClientSocket::run() {
    std::cout << "ClientSocket run" << std::endl;

    std::tuple<std::unique_ptr<Packet>, int> packet_client_id;

    std::unique_ptr<Packet> packet;

    #ifdef _WIN32
        inputThread = std::thread(&ClientSocket::read_input, this);

        while (loop) {
            init_fd_set();
            std::string message;
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (!input.empty()) {
                    message = input;
                    input.clear();
                }
            }
            if (!message.empty()) {
                std::unique_ptr<Packet> packet = std::make_unique<Packet>();
                packet->code = MESSAGE;
                packet->data_size = message.size();
                packet->data = malloc(packet->data_size);
                memcpy(packet->data, message.c_str(), packet->data_size);
                send(packet.get(), serv_addr);
            }
            if (FD_ISSET(sockfd, &_readfds)) {
                if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) > 0) {
                    receive();
                }
            }

        }

        inputThread.join();
    #elif defined(__unix__) || defined(__unix__)
        while (loop) {
            init_fd_set();
            listen_server();
            if (lastMessage == "exit") {
                break;
            }
        }
    #endif
}

std::tuple<std::unique_ptr<Packet>, int> ClientSocket::listen_server() {
    std::cout << "listen_server" << std::endl;
    int action = select(FD_SETSIZE, &_readfds, nullptr, nullptr, nullptr);
    std::cout << "action: " << action << std::endl;
    if (action == -1) {
        throw std::runtime_error("Error: select failed");
    } else if (action == 0) {
        throw std::runtime_error("Error: select timeout");
    } else {
        std::cout << "FD_ISSET(STDIN_FILENO, &_readfds): " << FD_ISSET(STDIN_FILENO, &_readfds) << std::endl;
        if (FD_ISSET(STDIN_FILENO, &_readfds)) {
            std::string message;
            if (!std::getline(std::cin, message)) {
                loop = false;
                return std::make_tuple(nullptr, 0);
            }
            std::unique_ptr<Packet> packet = std::make_unique<Packet>();
            packet->code = MESSAGE;
            packet->data_size = message.size();
            packet->data = malloc(packet->data_size);
            memcpy(packet->data, message.c_str(), packet->data_size);
            send(packet.get(), serv_addr);
        }
        if (FD_ISSET(sockfd, &_readfds)) {
            return receive();
        }
    }
}

void ClientSocket::init_fd_set() {
    FD_ZERO(&_readfds);
    #ifndef _WIN32
        FD_SET(STDIN_FILENO, &_readfds);
    #endif
    FD_SET(sockfd, &_readfds);
}
