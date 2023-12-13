//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_USOCKET_HPP
#define R_TYPE_SERVER_USOCKET_HPP

#include <string>


class USocket {
public:
    virtual ~USocket() = default;

    virtual void connect(const std::string& ip, int port) = 0;
    virtual void send(const std::string& message) = 0;
    virtual void receive() = 0;
};


#endif //R_TYPE_SERVER_USOCKET_HPP
