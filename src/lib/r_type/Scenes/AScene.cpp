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

void AScene::update(std::shared_ptr<Event> event)
{
    for (auto &entity : _entities) {
        for (auto &component : entity->getComponents()) {
            for (auto &service : _services) {
                service->update(event, component);
            }
        }
    }
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
