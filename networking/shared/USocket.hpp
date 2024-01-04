//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_USOCKET_HPP
#define R_TYPE_SERVER_USOCKET_HPP

#include <string>
#include <memory>
#include <sys/time.h>


#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>

    #define STDIN_FILENO 0
#elif defined(__unix__) || defined(__linux__)
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <SFML/Window/Event.hpp>

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

typedef struct key {
    int key;
    int type;
} Key;

typedef struct mouse {
    int x;
    int y;
    int type;
} Mouse;

typedef struct event {
    int eventType;
    int key;
} Event;

typedef struct packet {
    CODE code;
    int data_size;
    void *data;
} Packet;

typedef struct drawable {
    int id;
    float x;
    float y;
    float sizeHorizontal;
    float sizeVertical;
    int rectLeft;
    int rectTop;
    int rectWidth;
    int rectHeight;
} DrawablePacket;

//obsolete
typedef enum type {
    PLAYER,
    ENEMY,
    BULLET,
    BACKGROUND,
} Type;

//obsolete
typedef struct element {
    int id;
    float x;
    float y;
    int width;
    int height;
    Type type;
} Element;

typedef struct split_packet {
    CODE code;
    int packet_id;
    int max_packet_id;
    char data[1024];
} SplitPacket;

class USocket {
    public:
        virtual ~USocket() = default;

        virtual void send(Packet *packet, struct sockaddr_in dest) = 0;
        virtual std::tuple<std::unique_ptr<Packet>, int> receive() = 0;

        virtual void splitAndSend(Packet *packet, struct sockaddr_in dest) = 0;

        virtual void run() = 0;

        virtual void sendPacket(SplitPacket *packet, struct sockaddr_in dest) = 0;
};


#endif //R_TYPE_SERVER_USOCKET_HPP
