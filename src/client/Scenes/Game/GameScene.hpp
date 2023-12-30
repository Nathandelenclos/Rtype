/*
** EPITECH PROJECT, 2023
** Rtype
** File description:
** GameScene.cpp
*/

#pragma once

#include <iostream>
#include "../AScene.hpp"
#include "Components/Sprite/SpriteComponent.hpp"
#include "networking/shared/USocket.hpp"

class GameScene : public AScene {
public:
    GameScene(ClientCore *clientCore, std::shared_ptr<ClientSocket> socket);

    ~GameScene() override = default;
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;
    void receiveData() override;

    sf::Texture getTextureByType(Type type) const;
    void initTextures();

private:
    std::shared_ptr<ClientSocket> _socket;
    std::map<Type, sf::Texture> _textures;
};
