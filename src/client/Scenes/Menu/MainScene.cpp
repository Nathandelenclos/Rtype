//
// Created by talleux on 12/29/23.
//

#include "MainScene.hpp"

MainScene::MainScene(std::shared_ptr<ClientSocket> socket)
{
    _socket = std::move(socket);
    init_scene();
}

void MainScene::init_scene()
{
}
