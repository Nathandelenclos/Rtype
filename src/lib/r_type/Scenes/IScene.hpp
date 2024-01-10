//
// Created by talleux on 1/4/24.
//

#pragma once

#include <vector>
#include <memory>
#include "../../networking/server/ServerSocket.hpp"
#include "../components/IComponent.hpp"
#include "../services/IService.hpp"
#include "../services/Graphic.hpp"
#include "../services/Animation.hpp"
#include "../entities/IEntity.hpp"

class ISceneRType {
    public:
        virtual ~ISceneRType() = default;

        virtual void display() = 0;
        virtual void update(std::shared_ptr<Event> event, std::shared_ptr<Packet> packet, int id) = 0;
        virtual void pauseScene() = 0;
        virtual void resumeScene() = 0;
        virtual void stopScene() = 0;

        virtual void addEntity(std::shared_ptr<IEntity> entity) = 0;
        virtual std::vector<std::shared_ptr<IEntity>> getEntities() = 0;

        virtual void addService(std::shared_ptr<IService> service) = 0;
        virtual std::vector<std::shared_ptr<IService>> getServices() = 0;

        virtual void sendGameState(int clientId) = 0;
        virtual void broadcastGameState() = 0;

    protected:
        std::vector<std::shared_ptr<IEntity>> _entities;
        std::vector<std::shared_ptr<IService>> _services;
        std::shared_ptr<ServerSocket> _serverSocket;
};
