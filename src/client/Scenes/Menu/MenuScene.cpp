//
// Created by Talleux on 29/12/2023.
//

#include "MenuScene.hpp"

MenuScene::MenuScene()
{
    init_scene();
}

void MenuScene::init_scene()
{
    addComponent(std::make_unique<TextComponent>());
}
