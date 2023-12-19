//
// Created by talleux on 12/13/23.
//

#include "ClientSocket.hpp"
#include <stdexcept>
#include <iostream>
#include <arpa/inet.h>

ClientSocket::ClientSocket() {
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error("Failed to create socket");
    }
    std::cout << "Socket created successfully (fd: " << sockfd << ")" << std::endl;
}

ClientSocket::~ClientSocket() {
    close(sockfd);
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
    while (true) {
        std::string message;
        std::cout << "Enter message: ";
        std::getline(std::cin, message);
        send(message, serv_addr);
        receive();
        if (lastMessage == "exit") {
            break;
        }
    }
}
