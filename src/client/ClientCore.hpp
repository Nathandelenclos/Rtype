//
// Created by Talleux on 28/12/2023.
//

#pragma once

#include <map>
#include "../../networking/client/ClientSocket.hpp"
#include "Scenes/IScene.hpp"

class ClientCore {
    public:
        ClientCore();
        ~ClientCore() = default;

        bool init_socket(std::string ip, int port);

    private:
        std::unique_ptr<ClientSocket> _socket;
        std::map<std::string, std::unique_ptr<IScene>> _scenes;
};
