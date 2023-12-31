/*
** EPITECH PROJECT, 2023
** RType
** File description:
** GameScene.cpp
*/

#include "GameScene.hpp"
#include "ClientCore.hpp"
#include <utility>

GameScene::GameScene(ClientCore *clientCore, std::shared_ptr<ClientSocket> socket) : AScene(clientCore),
                                                                                     _socket(std::move(socket)) {
//    initTextures();
}

void GameScene::receiveData() {
    std::tuple<std::unique_ptr<Packet>, int> packet = _socket->receive();
    std::unique_ptr<Packet> p = std::move(std::get<0>(packet));

    if (p != nullptr) {
//        if (p->code == ELEMENT) {
//            std::shared_ptr<SpriteComponent> sprite = std::make_shared<SpriteComponent>(_clientCore, _socket);
//            auto *element = static_cast<Element*>(p->data);
//            sprite->setTexture(getTextureByType(element->type));
//            sprite->setPosition(element->x, element->y);
//        }
        if (p->code == HEARTBEAT) {
            timeval timerecv{};
            timeval now{};
            gettimeofday(&now, nullptr);
            timerecv = *static_cast<timeval *>(p->data);
            timersub(&now, &timerecv, &_pingTime);

            for (auto &component: _components) {
                if (component->getType() == ComponentType::TEXT) {
                    if (component->getAttribute() == "text ping") {
                        dynamic_cast<TextComponent *>(component.get())->setText(
                                "Ping: " + std::to_string(_pingTime.tv_sec * 1000 + _pingTime.tv_usec / 1000) + ", " +
                                std::to_string(_pingTime.tv_usec % 1000) + "ms");
                    }
                }
            }
        }
    }
}

sf::Texture GameScene::getTextureByType(Type type) const {
    return _textures.at(type);
}

void GameScene::initTextures() {
    _textures[Type::PLAYER] = sf::Texture();
    _textures[Type::PLAYER].loadFromFile("assets/sprite/player.png");
    _textures[Type::ENEMY] = sf::Texture();
    _textures[Type::ENEMY].loadFromFile("assets/sprite/enemy.png");
    _textures[Type::BULLET] = sf::Texture();
    _textures[Type::BULLET].loadFromFile("assets/sprite/bullet.png");
    _textures[Type::BACKGROUND] = sf::Texture();
    _textures[Type::BACKGROUND].loadFromFile("assets/sprite/background.png");
}

void GameScene::handleEvent(const sf::Event &event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            _clientCore->setCurrentScene("main");
            return;
        }
    }
    for (auto &component: _components) {
        component->handleEvent(event, window);
    }
}
