#include "ServerSocket.hpp"
#include <stdexcept>
#include <iostream>

ServerSocket::ServerSocket() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error("Failed to create socket");
    }
    std::cout << "Socket created successfully (fd: " << sockfd << ")" << std::endl;
}

ServerSocket::~ServerSocket() {
    close(sockfd);
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

void ServerSocket::send(const std::string& message) {
    if (sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        throw std::runtime_error("Failed to send message");
    }
}

void ServerSocket::receive() {
    char buffer[1024] = {0};
    struct sockaddr_in cli_addr{};
    socklen_t len = sizeof(cli_addr);
    if (recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&cli_addr, &len) < 0) {
        throw std::runtime_error("Failed to read from socket");
    }
    std::cout << "Received message from " << inet_ntoa(cli_addr.sin_addr) << ":" << ntohs(cli_addr.sin_port) << std::endl;
    std::cout << "Message: " << buffer << std::endl;
    lastMessage = buffer;
    lastClientAddress = cli_addr;
}

void ServerSocket::run() {
    while (true) {
        receive();
        if (lastMessage == "ping") {
            send("pong");
        }
        if (lastMessage == "exit")
            break;
    }
}