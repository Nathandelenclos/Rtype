//
// Created by nathan on 12/30/23.
//

#include "Server.hpp"

#include <utility>
#include <sys/time.h>

Server::Server(std::string const &ip, int port) {
    _serverSocket = std::make_unique<ServerSocket>();
    _gameLoader = std::make_unique<DLLoader>("../lib_r_type.so");
    _serverSocket->init_server(ip, port);
    _game = std::unique_ptr<IGame>(_gameLoader->getInstance("create", _serverSocket.get()));
    _packetHeartBeat = std::make_unique<Packet>();
}

std::ostream &operator<<(std::ostream &os, CODE const &packetCode) {
    switch (packetCode) {
        case CODE::ELEMENT:
            os << "ELEMENT";
            break;
        case CODE::EVENT:
            os << "EVENT";
            break;
        case CODE::LOGIN:
            os << "LOGIN";
            break;
        case CODE::LOGOUT:
            os << "LOGOUT";
            break;
        case CODE::MESSAGE:
            os << "MESSAGE";
            break;
        case CODE::UNDEFINED:
            os << "UNDEFINED";
            break;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, Element const &packetElement) {
    os << "Element: " << packetElement.id << " " << packetElement.x << " " << packetElement.y << " " << packetElement.type;
    return os;
}

std::ostream &operator<<(std::ostream &os, std::unique_ptr<Packet> &packet) {
    os << "Packet: " << packet->code << " " << packet->data_size;
    if (packet->code == CODE::ELEMENT) {
        os << static_cast<Element *>(packet->data);
    }
    if (packet->code == CODE::MESSAGE) {
        os << " " << "Message: " + std::string(static_cast<char *>(packet->data));
    }
    return os;
}

Packet packet{};

void Server::run() {
    while (true) {
        _serverSocket->init_fd_set();
        _packetClientId = _serverSocket->receive();
        _packet = std::move(std::get<0>(_packetClientId));

        /*for (auto service: _game->getServices()) {
            IService *service1 = dynamic_cast<IService *>(service);
            std::vector<IObject *> objects = _game->getObjects();
            IGame *game = _game.get();
            service1->update(game, _game->getObjects());
        }*/
        /*for (auto object: _game->getObjects()) {
            _serverSocket->broadcast(object->getPacket());
        }*/
        if (_packet) {
            if (_packet->code == HEARTBEAT) {
                gettimeofday(&_currentTime, nullptr);
                _receveidTime = *static_cast<timeval *>(_packet->data);
                _packetHeartBeat->code = HEARTBEAT;
                _packetHeartBeat->data_size = sizeof(timeval);
                _packetHeartBeat->data = malloc(_packetHeartBeat->data_size);
                timersub(&_currentTime, &_receveidTime, &_packetHeartBeatData);
                std::cout << "Ping: " << _packetHeartBeatData.tv_sec * 1000 + _packetHeartBeatData.tv_usec / 1000 << "ms" << std::endl;
                memcpy(_packetHeartBeat->data, &_currentTime, _packetHeartBeat->data_size);
                _serverSocket->send(_packetHeartBeat.get(), _serverSocket->getClientAddress(std::get<1>(_packetClientId)));
                free(_packetHeartBeat->data);
            }
            if (_packet->code == MESSAGE) {
                std::cout << "Message: " << static_cast<char *>(_packet->data) << std::endl;
                auto *packetConnectionAccepted = new Packet();
                packetConnectionAccepted->code = MESSAGE;
                packetConnectionAccepted->data_size = 19;
                packetConnectionAccepted->data = malloc(packetConnectionAccepted->data_size);
                memcpy(packetConnectionAccepted->data, "connection accepted", packetConnectionAccepted->data_size);
                _serverSocket->send(packetConnectionAccepted, _serverSocket->getClientAddress(std::get<1>(_packetClientId)));
                free(packetConnectionAccepted->data);
                delete packetConnectionAccepted;
            }
            free(_packet->data);
            _packet.reset();
            _packetClientId = std::tuple<std::unique_ptr<Packet>, int>(nullptr, 0);
        }
        //test (ça fonctionne ici mais pas ailleurs (reçois UNDEFINED packet sur le client depuis un send à un autre endroit qu'ici))
        /*packet.code = LOGIN;
        packet.data_size = 4;
        packet.data = malloc(packet.data_size);
        memcpy(packet.data, "test", packet.data_size);
        if (!_serverSocket->getClients().empty())
            _serverSocket->send(&packet, _serverSocket->getClientAddress(1));
        */
    }
}
