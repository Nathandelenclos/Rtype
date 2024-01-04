//
// Created by talleux on 1/4/24.
//

#include "Lobby.hpp"

LobbyScene::LobbyScene(std::shared_ptr<ServerSocket> serverSocket) : AScene(std::move(serverSocket))
{
    initScene();
}

void LobbyScene::initScene()
{
    initEntities();
    initServices();
}

void LobbyScene::initEntities()
{
    std::shared_ptr<IEntity> player = std::make_shared<IEntity>();

    std::shared_ptr<Drawable> sprite = std::make_shared<Drawable>();
    sprite->setPosition({50, 50});
    player->addComponent(sprite);

    addEntity(player);
}

void LobbyScene::initServices()
{
    std::shared_ptr<Graphic> graphic = std::make_shared<Graphic>(_serverSocket);

    addService(graphic);
}
