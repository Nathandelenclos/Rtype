//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_USOCKET_HPP
#define R_TYPE_SERVER_USOCKET_HPP

#include <string>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#elif defined(__unix__) || defined(__linux__)
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif


class USocket {
public:
    virtual ~USocket() = default;

    virtual void send(const std::string& message, struct sockaddr_in dest) = 0;
    virtual void receive() = 0;

    virtual void run() = 0;
};


#endif //R_TYPE_SERVER_USOCKET_HPP
