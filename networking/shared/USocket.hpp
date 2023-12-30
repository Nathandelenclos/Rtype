//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_USOCKET_HPP
#define R_TYPE_SERVER_USOCKET_HPP

#include <string>
#include <memory>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>

    #define STDIN_FILENO 0
#elif defined(__unix__) || defined(__linux__)
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

typedef enum code {
    UNDEFINED,
    EVENT,
    MESSAGE,
    LOGIN,
    LOGOUT,
    HEARTBEAT,
    ELEMENT,
} CODE;

typedef struct packet {
    CODE code;
    int data_size;
    void *data;
} Packet;

typedef enum type {
    PLAYER,
    ENEMY,
    BULLET,
    BACKGROUND,
} Type;

typedef struct element {
    int id;
    float x;
    float y;
    int width;
    int height;
    Type type;
} Element;

class USocket {
public:
    virtual ~USocket() = default;

    virtual void send(Packet *packet, struct sockaddr_in dest) = 0;
    virtual std::tuple<std::unique_ptr<Packet>, int> receive() = 0;

    virtual void run() = 0;
};


#endif //R_TYPE_SERVER_USOCKET_HPP
