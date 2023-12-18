//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_USOCKET_HPP
#define R_TYPE_SERVER_USOCKET_HPP

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class USocket {
public:
    virtual ~USocket() = default;

    virtual void send(const std::string& message) = 0;
    virtual void receive() = 0;

    virtual void run() = 0;
};


#endif //R_TYPE_SERVER_USOCKET_HPP
