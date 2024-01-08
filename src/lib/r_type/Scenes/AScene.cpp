//
// Created by talleux on 1/4/24.
//

#include "AScene.hpp"

#include <utility>

AScene::AScene(std::shared_ptr<ServerSocket> serverSocket)
{
    _serverSocket = std::move(serverSocket);
}

void AScene::addEntity(std::shared_ptr<IEntity> entity)
{
    _entities.push_back(std::move(entity));
}

std::vector<std::shared_ptr<IEntity>> AScene::getEntities()
{
    return _entities;
}

void AScene::addService(std::shared_ptr<IService> service)
{
    _services.push_back(std::move(service));
}

std::vector<std::shared_ptr<IService>> AScene::getServices()
{
    return _services;
}

void AScene::display()
{

}

void AScene::pauseScene()
{
}

void AScene::resumeScene()
{
}

void AScene::stopScene()
{
}

void AScene::sendGameState(int clientID)
{
    std::cout << "Sending game state to client " << clientID << std::endl;
    std::shared_ptr<Packet> packet = std::make_shared<Packet>();
    NewComponent newComponent{};

    for (auto &entity : _entities) {
        for (auto &component : entity->getComponents()) {
            auto drawable = std::dynamic_pointer_cast<Drawable>(component);
            if (drawable) {
                newComponent.id = drawable->_textureId;
                std::memcpy(&newComponent.attribute, drawable->getAttribute(), std::strlen(drawable->getAttribute()));
                newComponent.type = ComponentTypeSocket ::SPRITESOCKET;
                packet->code = NEW_COMPONENT;
                packet->data_size = sizeof(NewComponent);
                packet->data = malloc(packet->data_size);
                std::memcpy(packet->data, &newComponent, packet->data_size);
                std::cout << "Sending component " << static_cast<char *>(packet->data) << " to client " << clientID << std::endl;
                _serverSocket->send(packet.get(), _serverSocket->getClientAddress(clientID));
                free(packet->data);
            }
        }
    }
}

void AScene::broadcastGameState()
{
    std::cout << "Broadcasting game state" << std::endl;
    std::shared_ptr<Packet> packet = std::make_shared<Packet>();
    NewComponent newComponent{};

    for (auto &entity : _entities) {
        for (auto &component : entity->getComponents()) {
            auto drawable = std::dynamic_pointer_cast<Drawable>(component);
            if (drawable) {
                newComponent.id = drawable->_textureId;
                std::memcpy(&newComponent.attribute, drawable->getAttribute(), std::strlen(drawable->getAttribute()));
                newComponent.type = ComponentTypeSocket ::SPRITESOCKET;
                packet->code = NEW_COMPONENT;
                packet->data_size = sizeof(NewComponent);
                packet->data = malloc(packet->data_size);
                std::memcpy(packet->data, &newComponent, packet->data_size);
                std::cout << "Sending component " << static_cast<char *>(packet->data) << " to all clients" << std::endl;
                _serverSocket->broadcast(packet.get());
                free(packet->data);
            }
        }
    }
}
