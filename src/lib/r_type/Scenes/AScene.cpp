//
// Created by talleux on 1/4/24.
//

#include "AScene.hpp"

#include <utility>

/**
 * @brief Construct a new AScene:: AScene object
 * @param serverSocket
 */
AScene::AScene(std::shared_ptr<ServerSocket> serverSocket)
{
    _serverSocket = std::move(serverSocket);
}

/**
 * @brief addEntity, add an entity
 * @param entity
 */
void AScene::addEntity(std::shared_ptr<IEntity> entity)
{
    _entities.push_back(std::move(entity));
}

/**
 * @brief getEntities, get the entities
 * @return entities (std::vector<std::shared_ptr<IEntity>>)
 */
std::vector<std::shared_ptr<IEntity>> AScene::getEntities()
{
    return _entities;
}

/**
 * @brief addService, add a service
 * @param service
 */
void AScene::addService(std::shared_ptr<IService> service)
{
    _services.push_back(std::move(service));
}

/**
 * @brief getServices, get the services
 * @return services (std::vector<std::shared_ptr<IService>>)
 */
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

/**
 * @brief restartScene, restart the scene
 */
void AScene::restartScene()
{
    _entities.clear();
    _services.clear();
    initEntities();
    initServices();
}

/**
 * @brief sedGameState, send the game state
 * @param clientID
 */
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
                std::memset(&newComponent.attribute, 0, 16);
                std::memcpy(&newComponent.attribute, entity->getAttribute().c_str(), 16);
                 std::memcpy(&newComponent.attribute2, entity->getAttribute().c_str() + 8, 8);
                newComponent.type = ComponentTypeSocket ::SPRITESOCKET;
                packet->code = NEW_COMPONENT;
                packet->data_size = sizeof(NewComponent);
                packet->data = malloc(packet->data_size);
                std::memcpy(packet->data, &newComponent, packet->data_size);
                // std::cout << "Sending component " << static_cast<char *>(packet->data) << " to client " << clientID
                // << std::endl;
                _serverSocket->send(packet.get(), _serverSocket->getClientAddress(clientID));
                free(packet->data);
            }
        }
    }
}

/**
 * @brief broadcastGameState, broadcast the game state
 */
void AScene::broadcastGameState()
{
    std::shared_ptr<Packet> packet = std::make_shared<Packet>();
    NewComponent newComponent{};

    for (auto &entity : _entities) {
        for (auto &component : entity->getComponents()) {
            auto drawable = std::dynamic_pointer_cast<Drawable>(component);
            if (drawable) {
                newComponent.id = drawable->_textureId;
                std::memset(&newComponent.attribute, 0, 16);
                std::memcpy(&newComponent.attribute, drawable->getAttribute(), std::strlen(drawable->getAttribute()));
                newComponent.type = ComponentTypeSocket ::SPRITESOCKET;
                newComponent.x = std::get<0>(drawable->getPosition());
                newComponent.y = std::get<1>(drawable->getPosition());
                newComponent.sizeHorizontal = std::get<0>(drawable->getSize());
                newComponent.sizeVertical = std::get<1>(drawable->getSize());
                newComponent.rectLeft = std::get<0>(drawable->getRect());
                newComponent.rectTop = std::get<1>(drawable->getRect());
                newComponent.rectWidth = std::get<2>(drawable->getRect());
                newComponent.rectHeight = std::get<3>(drawable->getRect());
                packet->code = NEW_COMPONENT;
                packet->data_size = sizeof(NewComponent);
                packet->data = malloc(packet->data_size);
                std::memcpy(packet->data, &newComponent, packet->data_size);
                // std::cout << "Sending component " << static_cast<char *>(packet->data) << " to all clients" <<
                // std::endl;
                _serverSocket->broadcast(packet.get());
                free(packet->data);
            }
        }
    }
}
