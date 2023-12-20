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

void ClientSocket::init_client(std::string ip, int port) {
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address");
    }
}

void ClientSocket::send(const std::string& message, struct sockaddr_in dest) {
    if (sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr*)&dest, sizeof(dest)) < 0) {
        throw std::runtime_error("Failed to send message");
    }
}

void ClientSocket::receive() {
    char buffer[1024] = {0};
    struct sockaddr_in cli_addr{};
    socklen_t len = sizeof(cli_addr);
    if (recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&cli_addr, &len) < 0) {
        throw std::runtime_error("Failed to read from socket");
    }
    std::string message = buffer;
    if (message == "received") {
        std::cout << "(Ghost Mode) Received message from " << inet_ntoa(cli_addr.sin_addr) << ":" << ntohs(cli_addr.sin_port) << std::endl;
        return;
    }
    std::cout << "Received message from " << inet_ntoa(cli_addr.sin_addr) << ":" << ntohs(cli_addr.sin_port) << std::endl;
    std::cout << "Message: " << buffer << std::endl;
    lastMessage = buffer;
}

void ClientSocket::run() {
    while (loop) {
        std::string message;
        init_fd_set();
        listen_server();
        if (lastMessage == "exit") {
            break;
        }
    }
}

void ClientSocket::listen_server() {
    int action = select(FD_SETSIZE, &_readfds, nullptr, nullptr, nullptr);

    if (action == -1) {
        throw std::runtime_error("Error: select failed");
    } else if (action == 0) {
        throw std::runtime_error("Error: select timeout");
    } else {
        if (FD_ISSET(STDIN_FILENO, &_readfds)) {
            std::string message;
            if (!std::getline(std::cin, message)) {
                loop = false;
                return;
            }
            send(message, serv_addr);
        }
        if (FD_ISSET(sockfd, &_readfds)) {
            receive();
        }
    }
}

void ClientSocket::init_fd_set() {
    FD_ZERO(&_readfds);
    FD_SET(STDIN_FILENO, &_readfds);
    FD_SET(sockfd, &_readfds);
}
