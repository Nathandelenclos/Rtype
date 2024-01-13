//
// Created by talleux on 12/13/23.
//

#ifndef R_TYPE_SERVER_USOCKET_HPP
#define R_TYPE_SERVER_USOCKET_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <sys/time.h>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

#define STDIN_FILENO 0
#elif defined(__unix__) || defined(__linux__)
#include <SFML/Window/Event.hpp>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
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
    NEW_COMPONENT,
    DELETE_COMPONENT,
} CODE;

typedef enum {
    TEXTSOCKET,
    SPRITESOCKET,
    BUTTONSOCKET,
    INPUTSOCKET,
    VARIABLESOCKET,
    MUSICSOCKET,
    SOUNDSOCKET,
} ComponentTypeSocket;

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
    int id;
} Event;

typedef struct packet {
    CODE code;
    int data_size;
    void *data;
} Packet;

typedef union attribute {
    char data;
    std::uint64_t number;
} attribute_t;

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
    std::uint64_t attribute;
    std::uint64_t attribute2;
} DrawablePacket;

typedef struct newComponent {
    int id;
    float x;
    float y;
    float sizeHorizontal;
    float sizeVertical;
    int rectLeft;
    int rectTop;
    int rectWidth;
    int rectHeight;
    std::uint64_t attribute;
    std::uint64_t attribute2;
    ComponentTypeSocket type;
} NewComponent;

// obsolete
typedef enum type {
    MISSINGTXT,
    PLAYER,
    ENEMY,
    BULLET,
    BACKGROUND1,
    BACKGROUND2,
    BACKGROUND3,
    BACKGROUND4,
} Type;

// obsolete
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

class USocket
{
  public:
    virtual ~USocket() = default;

    virtual void send(Packet *packet, struct sockaddr_in dest) = 0;
    virtual std::tuple<std::unique_ptr<Packet>, int> receive() = 0;

    virtual void splitAndSend(Packet *packet, struct sockaddr_in dest) = 0;

    virtual void run() = 0;

    virtual void sendPacket(SplitPacket *packet, struct sockaddr_in dest) = 0;
};

#endif // R_TYPE_SERVER_USOCKET_HPP
