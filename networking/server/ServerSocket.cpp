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

void ServerSocket::send(const std::string& message, struct sockaddr_in client) {
    if (sendto(sockfd, message.c_str(), message.size(), 0, (struct sockaddr*)&client, sizeof(client)) < 0) {
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


void ServerSocket::receive() {
    char buffer[1024] = {0};
    struct sockaddr_in cli_addr{};
    socklen_t len = sizeof(cli_addr);
    if (recvfrom(sockfd, buffer, 1024, 0, (struct sockaddr*)&cli_addr, &len) < 0) {
        throw std::runtime_error("Failed to read from socket");
    }
    addClient(cli_addr);
    int id = getClientId(cli_addr);
    std::cout << "Received message from " << inet_ntoa(cli_addr.sin_addr) << ":" << ntohs(cli_addr.sin_port) << " (id: " << id << ")" << std::endl;
    std::cout << "Message: " << buffer << std::endl;
    lastMessage = buffer;
    lastClientAddress = cli_addr;
    send("received", cli_addr);
}

void ServerSocket::run() {
    while (true) {
        receive();
        if (lastMessage == "ping") {
            send("pong", lastClientAddress);
        }
        if (lastMessage == "exit")
            break;
    }
}