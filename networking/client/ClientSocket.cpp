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

    _isInit = false;

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

    Packet packet{};
    packet.code = MESSAGE;
    packet.data_size = 10;
    packet.data = malloc(packet.data_size);
    memcpy(packet.data, "connection", packet.data_size);

    send(&packet, serv_addr);
    free(packet.data);

    return true;
}

void ClientSocket::send(Packet *packet, struct sockaddr_in dest) {
    splitAndSend(packet, dest);
}

void ClientSocket::sendPacket(SplitPacket *packet, struct sockaddr_in dest) {
    char *buffer = static_cast<char *>(malloc(sizeof(SplitPacket)));
    memset(buffer, 0, sizeof(SplitPacket));
    //strcpy(buffer, "test");
    memcpy(buffer, packet, sizeof(SplitPacket));
    if (sendto(sockfd, reinterpret_cast<const char *>(buffer), sizeof(SplitPacket), 0, (struct sockaddr*)&dest, sizeof(dest)) < 0) {
        throw std::runtime_error("Failed to send packet");
    }
    free(buffer);
}

void ClientSocket::receivePacketAndAddToBuffer() {
    SplitPacket splitPacket{};
    struct sockaddr_in cli_addr{};
    timeval receveidTime{};
    socklen_t len = sizeof(cli_addr);
    char *buffer = static_cast<char *>(malloc(sizeof(SplitPacket)));
    memset(buffer, 0, sizeof(SplitPacket));
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) > 0) {
        if (recvfrom(sockfd, buffer, sizeof(SplitPacket), 0, (struct sockaddr*)&cli_addr, &len) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
        std::cout << "Received packet from " << inet_ntoa(cli_addr.sin_addr) << ":" << ntohs(cli_addr.sin_port) << std::endl;
    } else {
        free(buffer);
        return;
    }
    memcpy(&splitPacket, buffer, sizeof(SplitPacket));

    gettimeofday(&receveidTime, nullptr);
    _packetBuffer.emplace_back(std::make_unique<SplitPacket>(splitPacket), receveidTime);
    //std::cout << "Received packet type: " << splitPacket.code << std::endl;
    free(buffer);
}

std::unique_ptr<Packet> ClientSocket::getPacketFromBuffer() {
    std::unique_ptr<Packet> packet = std::make_unique<Packet>();
    int counter = 0;
    long long int size = 0;
    std::unique_ptr<struct timeval> currentTime = std::make_unique<struct timeval>();
    std::unique_ptr<struct timeval> diffTime = std::make_unique<struct timeval>();

    auto it2 = _packetBuffer.begin();
    while (it2 != _packetBuffer.end()) {
        auto &[splitPacketInBuffer, receveidTimeInBuffer] = *it2;
        if (splitPacketInBuffer->packet_id == 0 && splitPacketInBuffer->max_packet_id == 0) {
            packet->code = splitPacketInBuffer->code;
            packet->data_size = splitPacketInBuffer->max_packet_id * 1024;
            if (packet->data_size == 0) {
                packet->data_size = 1024;
            }
            packet->data = malloc(packet->data_size);
            memcpy(packet->data, splitPacketInBuffer->data, packet->data_size);
            it2 = _packetBuffer.erase(it2);
            return packet;
        } else {
            if (splitPacketInBuffer->packet_id == counter) {
                size += strlen(splitPacketInBuffer->data);
                counter++;
                if (counter == splitPacketInBuffer->max_packet_id) {
                    packet->code = splitPacketInBuffer->code;
                    packet->data_size = size;
                    packet->data = malloc(packet->data_size);
                    memset(packet->data, 0, packet->data_size);
                    int counterAssign = 0;
                    auto it = _packetBuffer.begin();
                    while (it != _packetBuffer.end()) {
                        auto &[splitPacketInBufferAssign, receveidTimeInBufferAssign] = *it;
                        if (splitPacketInBufferAssign->packet_id == counterAssign) {
                            memcpy((char *)packet->data + counterAssign * 1024, splitPacketInBufferAssign->data, strlen(splitPacketInBufferAssign->data));
                            it = _packetBuffer.erase(it);
                            counterAssign++;
                        } else {
                            ++it;
                        }
                    }
                    return packet;
                }
            } else {
                counter = 0;
                size = 0;
            }
        }
    }
    free(packet->data);

    auto it = _packetBuffer.begin();
    while (it != _packetBuffer.end()) {
        auto &[splitPacketInBuffer, receveidTimeInBuffer] = *it;
        gettimeofday(currentTime.get(), nullptr);
        timersub(currentTime.get(), &receveidTimeInBuffer, diffTime.get());
        if (diffTime->tv_sec > 0 || diffTime->tv_usec > 100000) {
            it = _packetBuffer.erase(it);
        } else {
            ++it;
        }
    }
    return nullptr;
}

std::tuple<std::unique_ptr<Packet>, int> ClientSocket::receive() {
    receivePacketAndAddToBuffer();
    std::unique_ptr<Packet> packet = getPacketFromBuffer();
    if (packet != nullptr) {
        return std::make_tuple(std::move(packet), 0);
    }
    return std::make_tuple(nullptr, 0);
}

/*std::tuple<std::unique_ptr<Packet>, int> ClientSocket::receive() {
    bool packet_corrupted = false;
    packet_test.code = UNDEFINED;
    struct sockaddr_in cli_addr_code{};
    socklen_t len_code = sizeof(cli_addr_code);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) > 0) {
        if (recvfrom(sockfd, reinterpret_cast<char *>(&packet_test.code), sizeof(int), 0, (struct sockaddr*)&cli_addr_code, &len_code) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
        if (packet_test.code == LOGIN) {
            std::cout << "packet.code == LOGIN" << std::endl;
            packet_corrupted = true;
        }
    } else {
        return std::make_tuple(nullptr, 0);
    }


    struct sockaddr_in cli_addr_size{};
    socklen_t len_size = sizeof(cli_addr_size);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) > 0) {
        if (recvfrom(sockfd, reinterpret_cast<char *>(&packet_test.data_size), sizeof(int), 0, (struct sockaddr*)&cli_addr_size, &len_size) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
        if (cli_addr_size.sin_addr.s_addr != cli_addr_code.sin_addr.s_addr || cli_addr_size.sin_port != cli_addr_code.sin_port) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        return std::make_tuple(nullptr, 0);
    }


    packet_test.data = malloc(packet_test.data_size + 1);
    memset(packet_test.data, 0, packet_test.data_size + 1);
    struct sockaddr_in cli_addr_data{};
    socklen_t len_data = sizeof(cli_addr_data);
    char *buffer = static_cast<char *>(malloc(packet_test.data_size + 1));
    memset(buffer, 0, packet_test.data_size + 1);
    if (select(sockfd + 1, &_readfds, nullptr, nullptr, timeout.get()) > 0) {
        if (recvfrom(sockfd, buffer, packet_test.data_size, 0, (struct sockaddr*)&cli_addr_data, &len_data) < 0) {
            throw std::runtime_error("Failed to read from socket");
        }
    } else {
        free(buffer);
        free(packet_test.data);
        return std::make_tuple(nullptr, 0);
    }
    memcpy(packet_test.data, buffer, packet_test.data_size);


    std::string message = reinterpret_cast<char *>(packet_test.data);
    if (message == "received") {
        std::cout << "(Ghost Mode) Received message from " << inet_ntoa(cli_addr_data.sin_addr) << ":" << ntohs(cli_addr_data.sin_port) << std::endl;
        return std::make_tuple(nullptr, 0);
    }
    lastMessage = message;
    return std::make_tuple(std::make_unique<Packet>(packet_test), -1);
}*/

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
    return std::make_tuple(nullptr, 0);
}

void ClientSocket::init_fd_set() {
    FD_ZERO(&_readfds);
    #ifndef _WIN32
        FD_SET(STDIN_FILENO, &_readfds);
    #endif
    FD_SET(sockfd, &_readfds);
}

bool ClientSocket::isInit() const {
    return _isInit;
}

void ClientSocket::setInit(bool init) {
    _isInit = init;
}

void ClientSocket::splitAndSend(Packet *packet, struct sockaddr_in dest) {
    std::unique_ptr<SplitPacket> splitPacket = std::make_unique<SplitPacket>();
    splitPacket->code = packet->code;
    int i;

    if (packet->data_size < 1024) {
        splitPacket->packet_id = 0;
        splitPacket->max_packet_id = 0;
        splitPacket->data[0] = '\0';
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
            splitPacket->packet_id = i;
            memset(splitPacket->data, 0, 1024);
            memcpy(splitPacket->data, (char *)packet->data + i * 1024 + 1, rest);
            sendPacket(splitPacket.get(), dest);
        }
        free(packet->data);
    }
}
